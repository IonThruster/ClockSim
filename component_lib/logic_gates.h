#pragma once

#include <ClockSim.h>

#include <iostream>
#include <stdlib.h>
#include <list>
#include <tuple>

// Basic 2 Input 1 Output Logic Gate
class LogicGateBase : public Combinatorial<bool, 2, bool, 1>
{
    bool config_done_;

public:
    using Base = Combinatorial<bool, 2, bool, 1>;

    LogicGateBase(std::string name) 
    : Base(name)
    , config_done_(false) {
        srand (0);
    }    

    void Configure(Port<bool>* in_1, Port<bool>* in_2, Port<bool>* out)
    {
        inputs_[0] = in_1;
        inputs_[1] = in_2;

        outputs_[0] = out;
        config_done_ = true;
    }

    virtual void Logic() = 0;

    void randomize_inputs()
    {
        *inputs_[0] = static_cast<bool>(rand() % 2); 
        *inputs_[1] = static_cast<bool>(rand() % 2);
    }

    void Update(size_t clock)
    {
        if(clock % 10 == 0)
        {
            randomize_inputs();
        }

        Logic();
    }

    void Init()
    {
        // Need to dereference properly
        *inputs_[0] = 0;
        *inputs_[1] = 0;
    }

    void generate_vcd_info(std::list< std::tuple<std::string, uint16_t> > &dumplist)
    {
        dumplist.push_back({name_ + "IN_1", 1});
        dumplist.push_back({name_ + "IN_2", 1});
        dumplist.push_back({name_ + "OUT", 1});
    }

    void DumpSignals(std::string module_name)
    {
        signal_dumper.dump_signal(module_name + "_" + name_ + "_IN_1", convert<bool, 1>(inputs_[0]->value()));
        signal_dumper.dump_signal(module_name + "_" + name_ + "_IN_2", convert<bool, 1>(inputs_[1]->value()));
        signal_dumper.dump_signal(module_name + "_" + name_ + "_OUT", convert<bool, 1>(outputs_[0]->value()));
    }
};


// 2 Input 1 Output AND Gate
class AndGate : public LogicGateBase
{

public:

    using Base = LogicGateBase;

    AndGate(std::string name) 
    : Base(name) { }    

    void Logic()
    {
        assert(config_done_);

        // Need to dereference properly
        *outputs_[0] = inputs_[0]->value() & inputs_[1]->value();
    }
};

// 2 Input 1 Output OR Gate
class OrGate : public LogicGateBase
{

public:

    using Base = LogicGateBase;

    OrGate(std::string name) 
    : Base(name) { }    

    void Logic()
    {
        assert(config_done_);

        // Need to dereference properly
        *outputs_[0] = inputs_[0]->value() | inputs_[1]->value();
    }
};

// 2 Input 1 Output NAND Gate
class NandGate : public LogicGateBase
{

public:

    using Base = LogicGateBase;

    NandGate(std::string name) 
    : Base(name) { }    

    void Logic()
    {
        assert(config_done_);

        // Need to dereference properly
        *outputs_[0] = !(inputs_[0]->value() & inputs_[1]->value());
    }
};

// 2 Input 1 Output NOR Gate
class NorGate : public LogicGateBase
{

public:

    using Base = LogicGateBase;

    NorGate(std::string name) 
    : Base(name) { }    

    void Logic()
    {
        assert(config_done_);

        // Need to dereference properly
        *outputs_[0] = !(inputs_[0]->value() | inputs_[1]->value());
    }
};
