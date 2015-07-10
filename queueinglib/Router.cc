//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


#include "Router.h"
#include "Job.h"
#include <string.h>

namespace queueing {

Define_Module(Router);

Router::Router(){

}

Router::~Router(){
    while (!jobsHeld.empty()) {
        delete jobsHeld.front();
        jobsHeld.pop_front();
    }
}

void Router::initialize()
{
    setPerformFinalGC(true);
    inizializzaVettori("valori", &valori);
    inizializzaVettori("repliche", &repliche);
    initLVector(valori.size(), &lValori);
    initLVector(repliche.size(), &lRepliche);


    PSVAL = valori.size() / 4;
    PSREP = repliche.size() / 4;
    i = 0;
    idRouter = par("idRouter");
    WATCH_PTRLIST(jobsHeld);
    oldValue = true;
}


//6,11,16,21
void Router::handleMessage(cMessage *msg)
{
    int x;

    int v = -1;
    int r = -1;
    bool a, b;
    bool cerca = true;
    int ID = par("id");
    idRouter = ID -1;
    Job *job = check_and_cast<Job *>(msg);


    x = job->getValue();
    a = searchValori(x, valori, &v);
    b = searchRepliche(x, repliche, &r);

    const char *name = msg->getName();

    if(strncmp(name, "Controlla", 9)==0){
        if(a || b){
            name = "Aggiornamento";
        }
        else{

            popQueue(job);
            send(job, "out", 0);
        }
    }

    if(strncmp(name, "Release", 7)==0){
        if(!oldValue){
            if(a){
                lValori[v] = false;
            }
            else if(b){
                lRepliche[r] = false;
            }
        }

        popQueue(job);
    }

    if(strncmp(name, "Aggiornamento", 13)==0){

        if(a || b){
            Job *child = job->dup();
            child->makeChildOf(job);

            char buf[256], buf2[256];
            sprintf(buf, "%s", "RichiestaLock");
            child->setName(buf);
            Job *child2 = child->dup();
            Job *child3 = child->dup();
            child2->makeChildOf(job);
            child3->makeChildOf(job);

            if(a){
                if(lValori[v]) {
                    sprintf(buf2, "%s", "Attendi");
                    child->setName(buf2);
                    send(child, "out", 5);
                }
                else{
                    lValori[v] = true;

                    send(child, "out", 2);
                    send(child2, "out", 3);
                    send(child3, "out", 4);
                }
            }
            else if(b){
                if(lRepliche[r]) {
                    sprintf(buf2, "%s", "Attendi");
                    child->setName(buf2);
                    send(child, "out", 5);
                }
                else{
                    lRepliche[r] = true;

                    send(child, "out", 2);
                    send(child2, "out", 3);
                    send(child3, "out", 4);
                }
            }

        }
        else NewFork(job, ID, "Controlla"); // ------------------------------
        //delete(job);
        //scheduleAt(simTime()+exponential(1.0), new cMessage);
    }



    if(strncmp(name, "RichiestaLock", 13)==0){
        //Job *child = job->dup();

        //child->makeChildOf(job->getParent());

        //delete(job);
        char buf[256];
        sprintf(buf, "%s", "Risposta");
        job->setName(buf);

        if(a){
            if(lValori[v]){
                job->setLocks(false);
                oldValue = false;
            }
            else{
                job->setLocks(true);
                lValori[v] = true;
            }
        }
        else if(b){
            if(lRepliche[r]){
                job->setLocks(false);
                oldValue = false;
            }
            else {
                job->setLocks(true);
                lRepliche[r] = true;
            }
        }else job->setLocks(true);


        int indice = msg->getSenderModuleId();

        int modID = getId();

        int outIndex = 0;
        switch (indice){
           case 6: {
               if(modID == 11) outIndex = 2;
               else if(modID == 16) outIndex = 4;
               else outIndex = 3;
               break;
           }
           case 11: {
               if(modID == 6) outIndex = 2;
               else if(modID == 16) outIndex = 2;
               else outIndex = 4;
               break;
           }
           case 16: {
               if(modID == 6) outIndex = 4;
               else if(modID == 11) outIndex = 3;
               else outIndex = 2;
               break;
           }
           case 21: {
               if(modID == 6) outIndex = 3;
               else if(modID == 11) outIndex = 4;
               else outIndex = 3;
               break;
           }
        }

       send(job, "out", outIndex);
       //delete(job);
    }

    if(strncmp(name, "Risposta", 8)==0){

        jobsHeld.push_back(job);
        Job *parent;

        parent = job->getParent();
        //ASSERT(parent != NULL);

        int subJobsHeld = 0;
        for (std::list<Job*>::iterator it=jobsHeld.begin(); it!=jobsHeld.end(); it++)
            if ((*it)->getParent() == parent)
                subJobsHeld++;

        if (subJobsHeld == parent->getNumChildren()) {
            take(parent);
            //std::vector<int> trueID;
            for (std::list<Job*>::iterator it=jobsHeld.begin(); it!=jobsHeld.end(); /*nop*/) {
                if ((*it)->getParent() != parent){
                    ++it;
                }
                else {
                    //if((*it)->getLocks()) trueID.push_back((*it)->getSenderModuleId());
                    cerca = cerca && (*it)->getLocks();
                    std::list<Job*>::iterator tmp = it++;
                    delete (*tmp);
                    jobsHeld.erase(tmp);
                }
            }

            parent->setLocks(cerca);

            if(cerca){
                NewFork(parent, ID, "Modifica");
            }
            else {
                if(a){
                    lValori[v] = false;
                }
                if(b){
                    lRepliche[r] = false;
                }

                NewFork(parent, ID, "Release");
            }
        }
    }


    if(strncmp(name, "Modifica", 8)==0){

        Job *child = job->dup();

        char buf[256];
        sprintf(buf, "%s", "inAggiornamento");
        child->setName(buf);

        if(a || b){
            send(child, "out", 1);
        }
        else{
            send(child, "out", 0);
        }

    }

    if(strncmp(name, "inAggiornamento", 15)==0){
        Job *child = job->dup();

        oldValue = true;

        char buf[256];
        sprintf(buf, "%s", "Eseguito");
        child->setName(buf);
        if(a){
            lValori[v] = false;
        }
        if(b){
            lRepliche[r] = false;
        }

        popQueue(job);

        send(child, "out", 0);
    }

    if(strncmp(name, "Lettura", 7)==0){
        int outIndex;
        Job* child = job->dup();

        if(a || b){
            if((v!=-1 && lValori[v]) || (r!=-1 && lRepliche[r])){
                char buf2[256];
                sprintf(buf2, "%s", "Attendi");
                child->setName(buf2);

                outIndex = 5;
            }
            else{

                char buf[256];
                sprintf(buf, "%s", "Letto");
                child->setName(buf);

                outIndex = 1;
            }
            send(child, "out", outIndex);
        }
        else NewFork(child, ID, "CtrlLettura");

        //scheduleAt(simTime()+exponential(1.0), new cMessage);

    }

    if(strncmp(name, "CtrlLettura", 11)==0){
        int outIndex;
        Job* child = job->dup();
        if(a || b){
            if((v!=-1 && lValori[v]) || (r!=-1 && lRepliche[r])){
                char buf2[256];
                sprintf(buf2, "%s", "Attendi");
                child->setName(buf2);

                outIndex = 5;
            }
            else{
                char buf[256];
                sprintf(buf, "%s", "Letto");
                child->setName(buf);
                outIndex = 1;
            }
            send(child, "out", outIndex);
        }
        else{

            popQueue(job);
            send(child, "out", 0);
        }
    }

    if(strncmp(name, "Letto", 5)==0){
        popQueue(job);
        send(job, "out", 0);
    }
}

void Router::NewFork(Job *job, int ID, const char *s){
        Job *child = job->dup();

        char buf[256];
        sprintf(buf, "%s", s);
        child->setName(buf);
        Job *child2 = child->dup();
        Job *child3 = child->dup();

        send(child, "out", 2);
        send(child2, "out", 3);
        send(child3, "out", 4);
}

void Router::inizializzaVettori(const char *s, std::vector<int> *x){
    const char *confronto = par(s);

   cStringTokenizer tokenizer(confronto);

   while (tokenizer.hasMoreTokens()){
      const char *token = tokenizer.nextToken();
      x->push_back(atof(token));
   }
}

void Router::initLVector(int size, std::vector<bool> *x){
    for(int j = 0; j < size; j++){
        x->push_back(false);
    }
}

bool Router::searchValori(int x, std::vector<int> vect, int *v){
    int output=false;
    for(int j = (idRouter-1)*PSVAL; j<=idRouter*PSVAL-1; j++){
        if(x==vect[j]){
            output=true;
            *v = j;
        }
    }

    return output;
}

bool Router::searchRepliche(int x, std::vector<int> vect, int *r){
    int output=false;
    for(int j = (idRouter-1)*PSREP; j<=idRouter*PSREP-1; j++){
        if(x==vect[j]){
            output=true;
            *r = j;
        }
    }

    return output;
}

bool Router::searchForLocks(int vIndex){
    if(vIndex==0) return true;
    return false;
}

void Router::popQueue(Job *job){
    Job *child = job->dup();

    char buf[256];
    sprintf(buf, "%s", "Invia");
    child->setName(buf);
    send(child, "out", 5);
}


};

