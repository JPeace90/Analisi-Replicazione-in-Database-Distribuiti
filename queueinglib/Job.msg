//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


namespace queueing;

cplusplus {{
#include "QueueingDefs.h"
}}

//
// Job message definition for queueing framework
//
message Job
{
    @customize(true);
    string displayString = "b=5,5,rect,white,kind,5";
    simtime_t time;
    int value;
    int type;
    bool locks;
    int priority;                // queueing priority
    simtime_t totalQueueingTime; // total time spent standing in queues
    simtime_t totalServiceTime;  // total time spent in servers
    simtime_t totalDelayTime;    // total time spent in delay modules
    int queueCount;              // the number of queue modules visited by the job
    int delayCount;              // the number of delay modules visited by the job
    int generation;              // how many times the original ancestor was copied
}


