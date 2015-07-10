/*
 * WaitQueue.cc
 *
 *  Created on: 20/feb/2015
 *      Author: Giovanni
 */

#include <WaitQueue.h>
#include <Job.h>
#include <string.h>
#include <Router.h>

namespace queueing {

Define_Module(WaitQueue);

WaitQueue::WaitQueue() {
    // TODO Auto-generated constructor stub

}

WaitQueue::~WaitQueue() {
    // TODO Auto-generated destructor stub
}

void WaitQueue::initialize(){
    waitTime = registerSignal("waitTime");
    time = registerSignal("time");
    i = 0;
}

void WaitQueue::handleMessage(cMessage *msg){
    Job *job = check_and_cast<Job *>(msg);
    SimTime regTime = 0;
    const char *name = job->getName();

    if(strncmp(name, "Wait", 4)==0){
        job->setTimestamp(simTime());
        //job->setQueueCount(job->getQueueCount()+1);

        i=i+1;
        std::cout << "JobN: " << i << " Sito: " << job->getSenderModuleId() << "   Value: " << job->getValue() << endl;
        queue.insert(job);
    }



    if(strncmp(name, "relJob", 6)==0){
        Job *child = NULL;

        if(!queue.empty()) child = (Job*)queue.pop();

        if(child != NULL){
            regTime = simTime()-child->getTime();
            child->setTime(regTime);

            ///
            emit(waitTime, simTime() - child->getTimestamp() );
            ///

            //emit(waitTime, regTime);
            emit(time, (SimTime)simTime());

            char buf[256];
            if(child->getType() == 0) sprintf(buf, "%s", "Read");
            else sprintf(buf, "%s", "Updating");

            child->setName(buf);
            //child->setQueueCount(child->getQueueCount()+1);

            i=i-1;
            std::cout << "Job-N: " << i << " Sito: " << child->getSenderModuleId() << "   Value: " << child->getValue() << endl;

            send(child, "out");
        }
    }

    if (ev.isGUI()) getDisplayString().setTagArg("i",1, !job ? "" : "cyan3");



}

}; //namespace


