/*!
 * \file control_thread_test.cc
 * \brief  This file implements tests for the ControlThread.
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *         Carles Fernandez-Prades, 2013. cfernandez(at)cttc.es
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2015  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */


#include <unistd.h>
#include <exception>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/exception_ptr.hpp>
#include <gtest/gtest.h>
#include <gnuradio/msg_queue.h>
#include <gnuradio/message.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "control_thread.h"
#include "in_memory_configuration.h"
#include "control_message_factory.h"


TEST(Control_Thread_Test, InstantiateRunControlMessages)
{
    std::shared_ptr<InMemoryConfiguration> config = std::make_shared<InMemoryConfiguration>();

    config->set_property("SignalSource.implementation", "File_Signal_Source");
    std::string path = std::string(TEST_PATH);
    std::string file = path + "signal_samples/GSoC_CTTC_capture_2012_07_26_4Msps_4ms.dat";
    const char * file_name = file.c_str();
    config->set_property("SignalSource.filename", file_name);
    config->set_property("SignalSource.item_type", "gr_complex");
    config->set_property("SignalSource.sampling_frequency", "4000000");
    config->set_property("SignalSource.repeat", "true");
    config->set_property("SignalConditioner.implementation", "Pass_Through");
    config->set_property("SignalConditioner.item_type", "gr_complex");
    config->set_property("Channels_GPS.count", "2");
    config->set_property("Channels_Galileo.count", "0");
    config->set_property("Channels.in_acquisition", "1");
    config->set_property("Channel.system", "GPS");
    config->set_property("Channel.signal", "1C");
    config->set_property("Acquisition_GPS.implementation", "GPS_L1_CA_PCPS_Acquisition");
    config->set_property("Acquisition_GPS.threshold", "1");
    config->set_property("Acquisition_GPS.doppler_max", "5000");
    config->set_property("Acquisition_GPS.doppler_min", "-5000");
    config->set_property("Tracking_GPS.implementation", "GPS_L1_CA_DLL_PLL_Tracking");
    config->set_property("Tracking_GPS.item_type", "gr_complex");
    config->set_property("TelemetryDecoder_GPS.implementation", "GPS_L1_CA_Telemetry_Decoder");
    config->set_property("TelemetryDecoder_GPS.item_type", "gr_complex");
    config->set_property("Observables.implementation", "GPS_L1_CA_Observables");
    config->set_property("Observables.item_type", "gr_complex");
    config->set_property("PVT.implementation", "GPS_L1_CA_PVT");
    config->set_property("PVT.item_type", "gr_complex");
    config->set_property("OutputFilter.implementation", "Null_Sink_Output_Filter");
    config->set_property("OutputFilter.item_type", "gr_complex");

    std::shared_ptr<ControlThread> control_thread = std::make_shared<ControlThread>(config);

    gr::msg_queue::sptr control_queue = gr::msg_queue::make(0);

    std::unique_ptr<ControlMessageFactory> control_msg_factory(new ControlMessageFactory());

    control_queue->handle(control_msg_factory->GetQueueMessage(0,0));
    control_queue->handle(control_msg_factory->GetQueueMessage(1,0));
    control_queue->handle(control_msg_factory->GetQueueMessage(200,0));

    control_thread->set_control_queue(control_queue);
    try
    {
            control_thread->run();
    }
    catch( boost::exception & e )
    {
            std::cout << "Boost exception: " << boost::diagnostic_information(e);
    }
    catch(std::exception const&  ex)
    {
            std::cout  << "STD exception: " << ex.what();
    }

    unsigned int expected3 = 3;
    unsigned int expected1 = 1;
    EXPECT_EQ(expected3, control_thread->processed_control_messages());
    EXPECT_EQ(expected1, control_thread->applied_actions());
}





TEST(Control_Thread_Test, InstantiateRunControlMessages2)
{
    std::shared_ptr<InMemoryConfiguration> config = std::make_shared<InMemoryConfiguration>();
    config->set_property("SignalSource.implementation", "File_Signal_Source");
    std::string path = std::string(TEST_PATH);
    std::string file = path + "signal_samples/GSoC_CTTC_capture_2012_07_26_4Msps_4ms.dat";
    const char * file_name = file.c_str();
    config->set_property("SignalSource.filename", file_name);
    config->set_property("SignalSource.item_type", "gr_complex");
    config->set_property("SignalSource.sampling_frequency", "4000000");
    config->set_property("SignalSource.repeat", "true");
    config->set_property("SignalConditioner.implementation", "Pass_Through");
    config->set_property("SignalConditioner.item_type", "gr_complex");
    config->set_property("Channels_GPS.count", "4");
    config->set_property("Channels_Galileo.count", "0");
    config->set_property("Channels.in_acquisition", "1");
    config->set_property("Channel.system", "GPS");
    config->set_property("Channel.signal", "1C");
    config->set_property("Acquisition_GPS.implementation", "GPS_L1_CA_PCPS_Acquisition");
    config->set_property("Acquisition_GPS.threshold", "1");
    config->set_property("Acquisition_GPS.doppler_max", "5000");
    config->set_property("Acquisition_GPS.doppler_min", "-5000");
    config->set_property("Tracking_GPS.implementation", "GPS_L1_CA_DLL_FLL_PLL_Tracking");
    config->set_property("Tracking_GPS.item_type", "gr_complex");
    config->set_property("TelemetryDecoder_GPS.implementation", "GPS_L1_CA_Telemetry_Decoder");
    config->set_property("TelemetryDecoder_GPS.item_type", "gr_complex");
    config->set_property("Observables.implementation", "GPS_L1_CA_Observables");
    config->set_property("Observables.item_type", "gr_complex");
    config->set_property("PVT.implementation", "GPS_L1_CA_PVT");
    config->set_property("PVT.item_type", "gr_complex");
    config->set_property("OutputFilter.implementation", "Null_Sink_Output_Filter");
    config->set_property("OutputFilter.item_type", "gr_complex");

    std::unique_ptr<ControlThread> control_thread2(new ControlThread(config));

    gr::msg_queue::sptr control_queue2 = gr::msg_queue::make(0);

    std::unique_ptr<ControlMessageFactory> control_msg_factory2(new ControlMessageFactory());

    control_queue2->handle(control_msg_factory2->GetQueueMessage(0,0));
    control_queue2->handle(control_msg_factory2->GetQueueMessage(2,0));
    control_queue2->handle(control_msg_factory2->GetQueueMessage(1,0));
    control_queue2->handle(control_msg_factory2->GetQueueMessage(3,0));
    control_queue2->handle(control_msg_factory2->GetQueueMessage(200,0));

    control_thread2->set_control_queue(control_queue2);

    try
    {
            control_thread2->run();
    }
    catch( boost::exception & e )
    {
            std::cout << "Boost exception: " << boost::diagnostic_information(e);
    }
    catch(std::exception const&  ex)
    {
            std::cout  << "STD exception: " << ex.what();
    }

    unsigned int expected5 = 5;
    unsigned int expected1 = 1;
    EXPECT_EQ(expected5, control_thread2->processed_control_messages());
    EXPECT_EQ(expected1, control_thread2->applied_actions());
}
