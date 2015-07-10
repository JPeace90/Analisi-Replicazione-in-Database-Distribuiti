/*
 * Controller.cc
 *
 *  Created on: 31/mar/2015
 *      Author: Giovanni
 */

#include <Controller.h>
#include "Job.h"
#include <string.h>

namespace queueing {

Define_Module(Controller);


Controller::Controller() {
    // TODO Auto-generated constructor stub

}

Controller::~Controller() {
    // TODO Auto-generated destructor stub
}

void Controller::initialize(){
    vInitialize("valori", &primary);
    vInitialize("repliche", &replicated);

    numSites=par("numSites");
    idRouter = par("idRouter");
    PSPRIM = primary.size() / numSites;
    PSREP = replicated.size() / numSites;

    ccIterated = 0;

    oldValue = true;

    WATCH_PTRLIST(jobsHeld);
    //setPerformFinalGC(true);
}

void Controller::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job *>(msg);
    const char *type = job->getName();
    int x = job->getValue();
    bool result = true;


    /*
    * Control
    * Mittente: altro sito
    * Se il dato è presente localmente, viene inviato un messsaggio di tipo Reset e comincia l'operazione di lettura
    * Se il dato non è presente, viene rinviato un messaggio di tipo Read al sito che ha effettuato la richiesta, il quale provvederà ad
    * effettuare la richiesta ad un altro sito.
    */
    if(strncmp(type, "Control", 7)==0){
        const char *name;

        if(job->getType()==0) name = "Read";
        else name = "Updating";

        if(search(x)){
            //new Job()
            renameSend(job->dup(), 0, "port$o", job->getArrivalGate()->getIndex(), "Reset");
            type = name;
        }
        else{
            renameSend(job->dup(), 0.8, "port$o", job->getArrivalGate()->getIndex(), name);
        }
    }


    /*
    * Read
    * Mittente: Source
    * Nessun lock: viene mandata l'operazione alla cpu che la esegue
    * Lock detenuto: il messaggio viene inviato alla WaitQueue
    * Dato non aggiornabile localmente: viene inviato un messaggio a ciascun sito(uno alla volta), il sito che detiene il dato effettua
    *                                  la lettura e manda un messaggio di tipo Reset al sito da cui era partita la richiesta. Se nessun
    *                                  sito ha presente il dato, il messaggio viene mandato alla sink.
    */
    if(strncmp(type, "Read", 4)==0){

        if(search(x)){
            if(!sLock(x)){
                //TODO nessun lock detenuto --> comincia la lettura
                renameSend(job->dup(), 0.5, "out", 0, "Finish");
            }
            else{
                //TODO Wait Queue
                renameSend(job->dup(), 0.5, "out", 2, "Wait");
            }
        }
        else{
            if(ccIterated < numSites-1) dataControl(job->dup(), ccIterated);
            else{
                ccIterated = 0;
                renameSend(job->dup(), 0.7,"out", 1, "Read");
                renameSend(new Job(), 0.7, "out", 2, "relJob");
            }
        }
    }


    /*
    * Updating
    * Mittente: Source
    * Nessun lock: viene effettuato il lock e la fork per richiedere i lock ai siti
    * Lock detenuto: il messaggio viene inviato alla WaitQueue
    * Dato non aggiornabile dal sito corrente: Viene mandato un messaggio a ciascun sito
    */
    if(strncmp(type, "Updating", 8)==0){

        if(search(x)){
            if(!sLock(x)){
                //TODO Richiesta Lock

                lock.push_back(job->getValue());
                NewFork(job, "Lock");
            }
            else{
                //TODO Wait Queue
                renameSend(job->dup(), 0.5, "out", 2, "Wait");
            }
        }
        else {
            //TODO Controlla
            if(ccIterated < numSites-1) dataControl(job->dup(), ccIterated);
            else{
                ccIterated = 0;
                renameSend(job->dup(), 0.7,"out", 1, "Updating");
                renameSend(new Job(), 0.7, "out", 2, "relJob");
            }
        }
    }


    /*
    * Lock
    * Mittente: altro sito
    * Feedback negativo: viene impostato il permesso a false e il valore di oldValue a false
    * Feedback positivo: viene aggiunto il valore al vettore dei lock e viene impostato il permesso a true
    */
    if(strncmp(type, "Lock", 4)==0){

        if(sLock(x)){
            //TODO feedback negativo
            oldValue = false;
            job->setLocks(false);
        }
        else{
            //TODO feedback positivo
            lock.push_back(job->getValue());
            job->setLocks(true);
        }
        renameSend(job, 1.0, "port$o", job->getArrivalGate()->getIndex(), "Answer");
    }


    /*
    * Answer
    * Mittente: altro sito
    * Vengono analizzate tutte le risposte.
    * result=true: viene fatta una fork con le informazioni di aggiornamento
    * result=false: vengono rilasciati i lock "locali" e viene fatta una fork che permette agli altri siti di rilasciare i lock
    */
    if(strncmp(type, "Answer", 6)==0){
        //TODO verifica risposta

        jobsHeld.push_back(job);
        Job *parent;

        parent = job->getParent();
        //ASSERT(parent != NULL); // still exists
        //std::cout << parent->getNumChildren() << endl;

        // count all sub-jobs with this parent
        int subJobsHeld = 0;
        for (std::list<Job*>::iterator it=jobsHeld.begin(); it!=jobsHeld.end(); it++)
            if ((*it)->getParent() == parent)
                subJobsHeld++;

        if (subJobsHeld == parent->getNumChildren()) {
            take(parent);
            for (std::list<Job*>::iterator it=jobsHeld.begin(); it!=jobsHeld.end(); ) {
                if ((*it)->getParent() != parent){
                    ++it;
                }
                else {
                    result = result && (*it)->getLocks();
                    std::list<Job*>::iterator tmp = it++;
                    //delete (*tmp);
                    jobsHeld.erase(tmp);
                }
            }

            if(result){
                NewFork(job,"Modify");
            }
            else{
                if(sLock(x)){
                    clearLock(x);
                    renameSend(new Job(), 0.7, "out", 2, "relJob");
                }
                NewFork(job, "Release");
            }
        }

    }


    /*
    * Modify
    * Mittente: altro sito
    * Viene mandato un messaggio alla cpu (simulazione dell'aggiornamento)
    */
    if(strncmp(type, "Modify", 6)==0){
        //TODO invio del messaggio alla cpu
        renameSend(job->dup(), 0.5, "out", 0, "Finish"); //invio del messaggio alla cpu
    }


    /*
    * Finish
    * Mittente: CodaCPU
    * Ultimato l'aggiornamento, vengono rilasciati i lock e viene mandato un messaggio alla sink
    */
    if(strncmp(type, "Finish", 6)==0){
        //TODO operazione terminata/rilascio lock
        if(job->getType()==1){
            oldValue = true;
            clearLock(x);
        }

        //invio del messaggio alla sink
        renameSend(job->dup(), 0.5, "out", 1, "Finish");
        //invio del messaggio alla WaitQueue
        renameSend(new Job(), 0.5,"out", 2, "relJob");

    }

    if(strncmp(type, "Reset", 5)==0){

        ccIterated = 0;

    }


    /*
     * Release
     * Mittente: sito che richiede i lock
     * Se qualche sito detiene già il lock sul dato da aggiornare, allora il sito "master" manda questo tipo di messaggio agli altri
     * siti che rilasciano i lock. Il sito "master" rilascia a sua volta il lock.
     */
    if(strncmp(type, "Release", 7)==0){
        //TODO rilascio dei lock - transazione abortita

        if(!oldValue){
            clearLock(x);
            renameSend(new Job(), 0.7, "out", 2, "relJob");
        }

    }

}


/*
 * search(int x)
 * Controlla se il valore(dato) passato come parametro è contenuto nel sito
 */
bool Controller::search(int x){
    bool output = false;

    for(int i = (idRouter-1)*PSPRIM; i <= idRouter*PSPRIM-1; i++){
        if(x == primary[i]) output = true;
    }

    for(int i = (idRouter-1)*PSREP; i <= idRouter*PSREP-1; i++){
        if(x == replicated[i]) output = true;
    }

    return output;
}


/*
 * vInitialize(const char *s, std::vector<int> *x)
 * Inizializza i vettori delle repliche e dei dati originali
 */
void Controller::vInitialize(const char *s, std::vector<int> *x){
    const char *parameter = par(s);

    cStringTokenizer tokenizer(parameter);

    while (tokenizer.hasMoreTokens()){
        const char *token = tokenizer.nextToken();
        x->push_back(atof(token));
    }
}


/*
 * sLock(int x)
 * Verifica la presenza di lock sul dato x
 */
bool Controller::sLock(int x){
    bool output = false;

    for(int i = 0; i<lock.size();i++){
        if(x==lock[i]) output = true;
    }

    return output;
}


/*
 * NewFork(Job *job, const char *s)
 * Metodo utilizzato per effettuare una "broadcast" a tutti gli altri siti
 */
void Controller::NewFork(Job *job, const char *s){
    char buf[256];
    sprintf(buf, "%s", s);
    job->setName(buf);

    for(int i = 0; i<gateSize("port$o"); i++){
        Job *child = job->dup();
        child->makeChildOf(job);

        sendDelayed(child, 1.5,"port$o", i);
        //send(child, "port$o", i);
    }
}


/*
 * renameSend(Job *job, simtime_t delay, const char *gate, int index, const char *s)
 * Metodo utilizzato per effettuare una send, modificando prima il nome del messaggio
 */
void Controller::renameSend(Job *job, simtime_t delay, const char *gate, int index, const char *s){
    Job *child = job;
    //child->makeChildOf(job->getParent());

    char buf[256];
    sprintf(buf, "%s", s);
    //job->setName(buf);
    child->setName(buf);

    sendDelayed(child, 1.0, gate, index);
}


/*
 * dataControl(Job *job, int pass)
 * Metodo utilizzato per la gestione delle operazioni remote
 */
void Controller::dataControl(Job *job, int pass){

    //std::cout << "ccIterated(dataControl): " << ccIterated << endl;
    char buf[256];
    sprintf(buf, "%s", "Control");
    job->setName(buf);

    send(job, "port$o", pass);
    ccIterated += 1;


}


/*
 * clearLock(int value)
 * Rilascio dei lock sui dati
 */
void Controller::clearLock(int value){
    for(int i = 0; i<lock.size(); i++){
        if(lock[i]==value){
            lock[i] = lock[lock.size() - 1];
            lock.pop_back();
        }
    }
}




};


/*
 * OPERAZIONI DI SCRITTURA E AGGIORNAMENTO
 *
 * Updating
 * Mittente: Source
 * Nessun lock: viene effettuato il lock e la fork per richiedere i lock ai siti
 * Lock detenuto: il messaggio viene inviato alla WaitQueue
 * Dato non aggiornabile dal sito corrente: Viene mandato un messaggio a ciascun sito
 *
 * Lock
 * Mittente: altro sito
 * Feedback negativo: viene impostato il permesso a false e il valore di oldValue a false
 * Feedback positivo: viene aggiunto il valore al vettore dei lock e viene impostato il permesso a true
 *
 * Answer
 * Mittente: altro sito
 * Vengono analizzate tutte le risposte.
 * result=true: viene fatta una fork con le informazioni di aggiornamento
 * result=false: vengono rilasciati i lock "locali" e viene fatta una fork che permette agli altri siti di rilasciare i lock
 *
 * Modify
 * Mittente: altro sito
 * Viene mandato un messaggio alla cpu (simulazione dell'aggiornamento)
 *
 * Finish
 * Mittente: CodaCPU
 * Ultimato l'aggiornamento, vengono rilasciati i lock e viene mandato un messaggio alla sink
 *
 */


/*
 * OPERAZIONI DI LETTURA
 *
 * Read
 * Mittente: Source
 * Nessun lock: viene mandata l'operazione alla cpu che la esegue
 * Lock detenuto: il messaggio viene inviato alla WaitQueue
 * Dato non aggiornabile localmente: viene inviato un messaggio a ciascun sito(uno alla volta), il sito che detiene il dato effettua
 *                                   la lettura e manda un messaggio di tipo Reset al sito da cui era partita la richiesta. Se nessun
 *                                   sito ha presente il dato, il messaggio viene mandato alla sink.
 *
 * Finish
 * Mittente: CodaCPU
 * Come le scritture
 *
 * Control
 * Mittente: altro sito
 * Se il dato è presente localmente, viene inviato un messsaggio di tipo Reset e comincia l'operazione di lettura
 * Se il dato non è presente, viene rinviato un messaggio di tipo Read al sito che ha effettuato la richiesta, il quale provvederà ad
 * effettuare la richiesta ad un altro sito.
 *
 * problema nelle letture: il reset arriva in ritardo e il job appena spawnato viene mandato direttamente nella sink senza essere prima controllato
 * RISOLTO: modifica del valore di interArrivalTime della Source
 */


