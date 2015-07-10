/*
 * WaitQueue.h
 *
 *  Created on: 20/feb/2015
 *      Author: Giovanni
 */

#ifndef WAITQUEUE_H_
#define WAITQUEUE_H_

#include "QueueingDefs.h"

namespace queueing{


class Job;


class QUEUEING_API WaitQueue : public cSimpleModule {
    public:
        WaitQueue();
        virtual ~WaitQueue();

        cQueue queue;
        int capacity;
        bool fifo;

    private:
        simsignal_t waitTime;
        simsignal_t time;
        int i;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};


}; //namespace

#endif /* WAITQUEUE_H_ */
