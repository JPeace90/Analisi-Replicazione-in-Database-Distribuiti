//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package org.omnetpp.queueing;

//
// Sends the messages to different outputs depending on a set algorithm.
//
// @author rhornig
// @todo minDelay not implemented
//
simple Router
{
    parameters:
        @group(Queueing);
        @display("i=block/routing");
        //string routingAlgorithm @enum("random","roundRobin","shortestQueue","minDelay") = default("random");
        //volatile double randomGateIndex = default(uniform(0, (out)-1));    // the destination gate in case of random routing
        //string distribution = default(".2 .2 .2 .16 .24");
        int id = default(0);
        string valori = default("0");
        string repliche = default("0");
        int idRouter = default(0);
        
    gates:
        input in[];
        output out[];
        inout port[];
}
