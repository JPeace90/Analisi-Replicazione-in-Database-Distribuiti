//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __QUEUEING_DEALLOCATE_H
#define __QUEUEING_DEALLOCATE_H

#include "QueueingDefs.h"
#include "ResourcePool.h"

namespace queueing {

class Job;

/**
 * Releases allocated resources on the arrival of each job.
 * See NED file for more info.
 */
class QUEUEING_API Deallocate : public cSimpleModule
{
    protected:
        IResourcePool *resourcePool;
        int resourceAmount;
        int obs;
        int nObs;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
};

}; // namespace

#endif
