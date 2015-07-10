/*
 * Controller.h
 *
 *  Created on: 31/mar/2015
 *      Author: Giovanni
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "QueueingDefs.h"
#include "Job.h"
#include <list>

namespace queueing{

class QUEUEING_API Controller : public cSimpleModule {
public:
    int PSPRIM, PSREP, numSites, idRouter, ccIterated;

    Controller();
    virtual ~Controller();

protected:
    bool oldValue;
    std::vector<int> lock;
    std::vector<int> primary;
    std::vector<int> replicated;
    std::list<Job*> jobsHeld;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual bool search(int x);
    virtual void vInitialize(const char *s, std::vector<int> *x);
    virtual bool sLock(int x);
    virtual void NewFork(Job *job, const char *s);
    virtual void renameSend(Job *job, simtime_t delay, const char *gate, int index, const char *s);
    virtual void dataControl(Job *job, int pass);
    virtual void clearLock(int value);

};

};
#endif /* CONTROLLER_H_ */

