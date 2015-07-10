//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __QUEUEING_ROUTER_H
#define __QUEUEING_ROUTER_H

#include "QueueingDefs.h"
#include "Job.h"
#include <list>


namespace queueing {

// routing algorithms
enum {
     ALG_RANDOM,
     ALG_ROUND_ROBIN,
     ALG_MIN_QUEUE_LENGTH,
     ALG_MIN_DELAY,
     ALG_MIN_SERVICE_TIME,
     ALG_NEW_DISTRIBUTION
};

/**
 * Sends the messages to different outputs depending on a set algorithm.
 */
class QUEUEING_API Router : public cSimpleModule
{
    private:
        //int routingAlgorithm;  // the algorithm we are using for routing
        int rrCounter;         // msgCounter for round robin routing
        int PSVAL, PSREP;
        int id, i;
        int idRouter;
        bool oldValue;
        //int distribution;

    public:
        Router();
        ~Router();
        std::list<Job*> jobsHeld;
        std::vector<int> valori;
        std::vector<int> repliche;
        std::vector<bool> lValori;
        std::vector<bool> lRepliche;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual void NewFork(Job *job, int ID, const char *s);
        //virtual void NewJoin(cMessage *msg, const char *s);
        virtual bool searchValori(int x, std::vector<int> vect, int *v);
        virtual bool searchRepliche(int x, std::vector<int> vect, int *r);
        virtual bool searchForLocks(int vIndex);
        virtual void inizializzaVettori(const char *s, std::vector<int> *x);
        virtual void initLVector(int size, std::vector<bool> *x);
        virtual void popQueue(Job *job);
};

}; //namespace

#endif

/*
 *
 *
 * //
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __QUEUEING_ROUTER_H
#define __QUEUEING_ROUTER_H

#include "QueueingDefs.h"

namespace queueing {

// routing algorithms
enum {
     ALG_RANDOM,
     ALG_ROUND_ROBIN,
     ALG_MIN_QUEUE_LENGTH,
     ALG_MIN_DELAY,
     ALG_MIN_SERVICE_TIME,
     ALG_NEW_DISTRIBUTION
};


class QUEUEING_API Router : public cSimpleModule
{
    private:


        int routingAlgorithm;  // the algorithm we are using for routing
        int rrCounter;         // msgCounter for round robin routing

        int distribution;
        std::vector<double> pSum;


    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

}; //namespace

#endif
 *
 *
 * */
