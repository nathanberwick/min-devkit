/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

#include "c74_min.h"

using namespace c74::min;

class bangMute : public object<bangMute>, public vector_operator<> {
public:
    MIN_DESCRIPTION	{ "Read from a buffer~." };
    MIN_TAGS		{ "audio, sampling" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "index~, buffer~, wave~" };

    inlet<>     audio_inlet     {this, "(signal) audio in", "signal"};
    //inlet<>		index_inlet		{ this, "(bang) bang inlet" }; //NOT ACTUALLY NECESSARY
    outlet<>	output			{ this, "(signal) Sample value at index", "signal" };

    message<> dspsetup {this, "dspsetup",
        MIN_FUNCTION {
           m_one_over_samplerate = 1.0 / samplerate();
           return {};
       }
    };

    message<> bang { this, "bang", "Mute the frame",
                     MIN_FUNCTION {
        //WE CAN CHECK WHAT INLET WE'RE USING HERE
        //TODO: how to check for inlet
                        m_bangFlag = true;
                         return {};
                     }
    };

    void operator()(audio_bundle input, audio_bundle output) {
        if (!m_bangFlag)
        {
            output = input;
            return;
        }
        output.clear();
        m_bangFlag = false;
    }

private:
    bool m_bangFlag {false};
    double m_one_over_samplerate	{ 1.0 };
};


MIN_EXTERNAL(bangMute);
