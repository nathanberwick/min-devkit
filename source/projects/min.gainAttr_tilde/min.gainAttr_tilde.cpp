/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"

using namespace c74::min;


class myGain : public object<myGain>, public vector_operator<> {
public:
    MIN_DESCRIPTION	{ "Read from a buffer~." };
    MIN_TAGS		{ "audio, sampling" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "index~, buffer~, wave~" };

    inlet<>  m_inlet	    { this, "(signal) Audio in", "signal"};
    inlet<>  m_inlet_channel	{ this, "(float) gain" };
    outlet<> m_outlet		{ this, "(signal) Audio Out", "signal" };

    myGain(const atoms& args = {}) {
        if (args.empty())
            cout << "no args" << endl;
        else if (args.size() > 0)
            m_initGain = args[0];
		else
		    cout << "too many args args" << endl;
    }


    attribute<number> m_gainMult {this, "gain", 1.0f,
                                 description {"gain multiplier"}
    };


    argument<float> m_gainArg {this, "gain", "gain multiplier",
        MIN_ARGUMENT_FUNCTION {
            m_gainMult = arg;
        }
    };



    void operator()(audio_bundle input, audio_bundle output) {
        //shush, I'm lazy.
        output = input;

        //yeah, this is very expanded but better to see what's going on right?
        for (int i = 0; i < output.channel_count(); ++i)
        {
            for (int j = 0; j < output.frame_count(); ++j)
            {
                output.samples(i)[j] *= m_gainMult;
            }
        }
    }

private:
    float m_initGain = 0.0f;
};


MIN_EXTERNAL(myGain);
