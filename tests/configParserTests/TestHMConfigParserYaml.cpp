// Copyright 2019, Oath Inc.
// Licensed under the terms of the Apache 2.0 license. See LICENSE file in the root of the distribution for licensing details.
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "common.h"
#include "HMConfigParserYaml.h"
#include "HMDataHostGroup.h"
#include "HMDataCheckParams.h"

#include "TestHMConfigParserYaml.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(TESTNAME);

void
TESTNAME::setUp()
{
    setupCommon();
    mkdir(folderLocation1.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir(folderLocation.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir(garbageLocation.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    ofstream fout(fileLocation);
    ofstream fout2(garbageConfig);
    ofstream fout3(fileLocation1);
    ofstream fout4(fileLocation2);
    ofstream fout5(wrongConfig);
    ofstream fout6(fileLocation3);
    ofstream fout7(fileLocation4);

    fout << "-   name: config.parse1.netchasm.net\n\
    allow-hosts: any\n\
    ttl: 60000\n\
    error-ttl: 2\n\
    failure-response: all\n\
    check-type: tcp\n\
    check-port: 123\n\
    check-info: hm-hello\n\
    check-retries:  2\n\
    check-retry-delay:  3\r\n\
    timeout: 2000\n\
    group-threshold: 12\n\
    slow-threshold: 34\n\
    smoothing-window: 5\n\
    rt-mode: total\n\
    flap-threshold: 12000\n\
    max-flaps: 3\n\
    conn-check-interval: 23123\n\
    dual-stack-mode: both\n\
    host:\n\
        - loadfb3.hm1.com\n\
        -  loadfb3.hm2.com\n\
    \n\
-   name: config.parse2.netchasm.net\n\
    allow-hosts: any\n\
    check-info: //hm/checkinfo\n\
    check-port:  80\n\
    check-type: http\n\
    dual-stack-mode: ipv4-only\n\
    rt-mode: connect\n\
    failure-response:  none\n\
    ttl:   60000\n\
    timeout: 10000\n\
    host:\n\
        - media-router.hm1.com\n\
        - media-router.hm2.com\n\
    \n\
-   name: config.parse3.netchasm.net\n\
    dual-stack-mode: ipv6-only\n\
    check-info: //hm/checkinfo-ssl\n\
    check-port:  443\n\
    rt-mode: smoothed-total\n\
    check-type: https-no-peer-check\n\
    ttl:   300000\n\
    host:\n\
        - e1.hm1.com\n\
        - e2.hm2.com\n\
    \n\
-   name: config.parse4.netchasm.net\n\
    ttl:   60000\n\
    timeout: 10000\n\
    rt-mode: smoothed-connect\n\
    check-type: dnsvc\n\
    check-info: healthcheck.hm.com\n\
    host:\n\
        - g4.hm1.com\n\
    \n\
-   name: config.parse5.netchasm.net\n\
    check-info: netchasm:y\\treexrzindaaR3zuqhnjpcqqtwM8xq@/\n\
    check-port:  21\n\
    check-type: ftp\n\
    timeout: 10000\n\
    host:\n\
        - dh1.hm1.com\n\
        - dh2.hm1.com\n\
    \n\
-   name: config.parse6.netchasm.net\n\
    check-type: http-auxfetch\n\
    check-info: /a00.netchasm.net.xml\n\
    host:\n\
        - loadfb.hm1.com\n\
        - loadfb.hm2.com\n\
    \n\
-   name: config.parse7.netchasm.net\n\
    failure-response:  dns\n\
    dual-stack-mode: both\n\
    check-type: https\n\
    \n\
-   name: config.parse8.netchasm.net\n\
    check-type: dns\n\
    \n\
-   name: config.parse9.netchasm.net\n\
    check-type: ftps\n\
    \n\
-   name: config.parse10.netchasm.net\n\
    check-type: ftps-explicit-no-peer-check\n\
    \n\
-   name: config.parse11.netchasm.net\n\
    check-type: ftp\n\
    \n\
-   name: config.parse12.netchasm.net\n\
    uri:  random.netchasm.com\n\
    \n\
-   name: config.parse13.netchasm.net\n\
    check-type: https-auxfetch\n\
    \n\
-   name: config.parse14.netchasm.net\n\
    check-type: https-no-peer-check-auxfetch\n\
    host:\n\
        - lfb.hm.com\n\
    \n\
-   name: config.parse15.netchasm.net\n\
    check-type: https-no-peer-check-auxfetch\n\
    host:\n\
        - lfb.hm.com" << endl;

    fout2 << "-   rt-mode total\n\
-   name: fail.netchasm.com\n\
    rt-mode: garbage\n\
    dual-stack-mode: garbage\n\
    check-type: garbage\n\
    failure-response: garbage\n\
    garbage: trashwaste\n" << endl;

fout3 << "-   name: config.parse.http.netchasm.net\n\
    check-type: http-auxfetch\n\
    rt-mode: total" << endl;

fout4 << "-   name: config.parse.https.netchasm.net\n\
    check-type: https-auxfetch" << endl;

fout5 << "-   name: config.parse.https.netchasm.net\n\
    check-type: https-auxfetch" << endl;

fout6 << "-   name: config.parse1.netchasm.net\n\
    allow-hosts: any\n\
    ttl: 60000\n\
    error-ttl: 2\n\
    failure-response: all\n\
    check-type: tcp\n\
    check-port: 123\n\
    check-info: hm-hello\n\
    check-retries:  2\n\
    check-retry-delay:  3\r\n\
    timeout: 2000\n\
    group-threshold: 12\n\
    slow-threshold: 34\n\
    smoothing-window: 5\n\
    rt-mode: total\n\
    flap-threshold: 12000\n\
    max-flaps: 3\n\
    conn-check-interval: 23123\n\
    dual-stack-mode: both\n\
    host:\n\
        - loadfb3.hm1.com\n\
        -  loadfb3.hm2.com\n";

fout7<<"-   name: config.parse2.netchasm.net\n\
    allow-hosts: any\n\
    check-info: //hm/checkinfo\n\
    check-port:  80\n\
    check-type: http\n\
    dual-stack-mode: ipv4-only\n\
    rt-mode: connect\n\
    failure-response:  none\n\
    ttl:   60000\n\
    timeout: 10000\n\
    host:\n\
        - media-router.hm1.com\n\
        - media-router.hm2.com\n";

    fout.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();
    fout6.close();
    fout7.close();

}
void
TESTNAME::tearDown()
{
    teardownCommon();
    remove(fileLocation.c_str());
    remove(folderLocation.c_str());
    remove(garbageConfig.c_str());
    remove(garbageLocation.c_str());
    remove(fileLocation1.c_str());
    remove(fileLocation2.c_str());
    remove(wrongConfig.c_str());
    remove(fileLocation3.c_str());
    remove(fileLocation4.c_str());

}

void
TESTNAME::test_config1_tests()
{
    string name = "config.parse1.netchasm.net";
    string info = "hm-hello";
    string host0 = "loadfb3.hm1.com";
    string host1 = "loadfb3.hm2.com";
    HMConfigParserYAML parse;
    HMDataCheckParams k, t;

    uint8_t numCheckRetries = 2;
    uint8_t checkRetryDelay = 3;
    uint16_t flags = HM_RT_TOTAL;
    uint32_t smoothingWindow = 5;
    uint32_t groupThreshold = 12;
    uint32_t slowThreshold = 34;
    uint32_t maxFlaps = 3;
    uint64_t checkTimeout = 2000;
    uint64_t checkTTL = 60000;
    uint32_t flapThreshold = 12;
    uint32_t passThrough = 0;

    k.setCheckParameters(numCheckRetries, checkRetryDelay,
            flags, smoothingWindow, groupThreshold, slowThreshold, maxFlaps,
            checkTimeout, checkTTL, flapThreshold, passThrough);

    CPPUNIT_ASSERT(parse.parseConfig(fileLocation,currentState) == 0);

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    CPPUNIT_ASSERT(hi.getCheckParameters(t));
    CPPUNIT_ASSERT_EQUAL(true, k == t);

    CPPUNIT_ASSERT_EQUAL(60000, (int)hi.getCheckTTL());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_TCP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(123, (int)hi.getCheckPort());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_RT_TOTAL,
            (unsigned int)(hi.getMeasurementOptions() & HM_RT_TOTAL));
    CPPUNIT_ASSERT_EQUAL(2000, (int)hi.getCheckTimeout());
    CPPUNIT_ASSERT_EQUAL(12, (int)hi.getGroupThreshold());
    CPPUNIT_ASSERT_EQUAL(info, hi.getCheckInfo());
    CPPUNIT_ASSERT_EQUAL(12, (int)hi.getFlapThreshold());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_DUALSTACK_BOTH,
            (unsigned int)hi.getDualstack() & HM_DUALSTACK_BOTH);
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((uint32_t)flapThreshold,
                hi.getFlapThreshold());
    const std::vector<std::string>* hostslist = hi.getHostList();
    CPPUNIT_ASSERT_EQUAL(hostslist->at(0), host0);
    CPPUNIT_ASSERT_EQUAL(hostslist->at(1), host1);
}

void
TESTNAME::test_config2_tests()
{
   string name = "config.parse2.netchasm.net";
    string info = "//hm/checkinfo";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL(60000, (int)hi.getCheckTTL());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_HTTP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(80, (int)hi.getCheckPort());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_RT_CONNECT,
            (unsigned int)(hi.getMeasurementOptions() & HM_RT_CONNECT));
    CPPUNIT_ASSERT_EQUAL(10000, (int)hi.getCheckTimeout());
    CPPUNIT_ASSERT_EQUAL(info, hi.getCheckInfo());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_DUALSTACK_IPV4_ONLY,
            (unsigned int)hi.getDualstack() & HM_DUALSTACK_IPV4_ONLY);
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());

}

void
TESTNAME::test_config3_tests()
{
    string name = "config.parse3.netchasm.net";
    string info = "//hm/checkinfo-ssl";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL(300000, (int)hi.getCheckTTL());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_HTTPS_NO_PEER_CHECK, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(443, (int)hi.getCheckPort());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_RT_SMOOTHED_TOTAL,
            (unsigned int)(hi.getMeasurementOptions() & HM_RT_SMOOTHED_TOTAL));
    CPPUNIT_ASSERT_EQUAL(info, hi.getCheckInfo());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_DUALSTACK_IPV6_ONLY,
            (unsigned int)hi.getDualstack() & HM_DUALSTACK_IPV6_ONLY);
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
   
}

void
TESTNAME::test_config4_tests()
{
   string name = "config.parse4.netchasm.net";
    HMConfigParserYAML parse;
    HMDataHostGroupMap hostGroups;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL(60000, (int)hi.getCheckTTL());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_DNSVC, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)HM_RT_SMOOTHED_CONNECT,
            (unsigned int)(hi.getMeasurementOptions() & HM_RT_SMOOTHED_CONNECT));
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());

}

void
TESTNAME::test_config5_tests()
{
    string name = "config.parse5.netchasm.net";
    string info = "netchasm:y\\treexrzindaaR3zuqhnjpcqqtwM8xq@/";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_FTP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(21, (int)hi.getCheckPort());
    CPPUNIT_ASSERT_EQUAL(10000, (int)hi.getCheckTimeout());
    CPPUNIT_ASSERT_EQUAL(info, hi.getCheckInfo());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());

}

void
TESTNAME::test_config6_tests()
{
    string name = "config.parse6.netchasm.net";
    string info = "/a00.netchasm.net.xml";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(info, hi.getCheckInfo());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(30000, (int)hi.getCheckTTL());
    CPPUNIT_ASSERT_EQUAL(80, (int)hi.getCheckPort());
}

void
TESTNAME::test_config7_tests()
{
    string name = "config.parse7.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_HTTPS, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((int)HM_DUALSTACK_BOTH, (int)hi.getDualstack());
}

void
TESTNAME::test_config8_tests()
{
    string name = "config.parse8.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_DNS, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(53, (int)hi.getCheckPort());
}

void
TESTNAME::test_config9_tests()
{
    string name = "config.parse9.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_FTPS_EXPLICIT, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(21, (int)hi.getCheckPort());
}

void
TESTNAME::test_config10_tests()
{
    string name = "config.parse10.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_FTPS_EXPLICIT_NO_PEER_CHECK, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(21, (int)hi.getCheckPort());
}

void
TESTNAME::test_config11_tests()
{
    string name = "config.parse11.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_FTP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(21, (int)hi.getCheckPort());
}

void
TESTNAME::test_config12_tests()
{
    string name = "config.parse12.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());

    HMDataHostGroup hi = it->second;

    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
}

void
TESTNAME::test_config13_tests()
{
   string name = "config.parse13.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTPS, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(443, (int)hi.getCheckPort());
}

void
TESTNAME::test_config14_tests()
{
   string name = "config.parse14.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTPS_NO_PEER_CHECK, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(443, (int)hi.getCheckPort());
}

void
TESTNAME::test_config15_tests()
{
   string name = "config.parse15.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(parse.parseConfig(fileLocation, currentState) == 0);

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTPS_NO_PEER_CHECK, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(443, (int)hi.getCheckPort());
}

void
TESTNAME::test_config_http_tests()
{
   string name = "config.parse.http.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(parse.parseConfig(fileLocation1, currentState) == 0);

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTP, (int)hi.getCheckType());
    CPPUNIT_ASSERT_EQUAL(80, (int)hi.getCheckPort());

}

void
TESTNAME::test_config_https_tests()
{
   string name = "config.parse.https.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(parse.parseConfig(fileLocation2, currentState) == 0);

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it != currentState.m_hostGroups.end());
    
    HMDataHostGroup hi = it->second;
    
    CPPUNIT_ASSERT_EQUAL((unsigned int)0,
            (unsigned int)hi.getPassthroughInfo());
    CPPUNIT_ASSERT_EQUAL(443, (int)hi.getCheckPort());
    CPPUNIT_ASSERT_EQUAL((int)HM_CHECK_AUX_HTTPS, (int)hi.getCheckType());
}

void TESTNAME::test_config_neg_tests()
{
    string name = "config.parse20.netchasm.net";
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(!HMConfigParserBase::parseDirectory(folderLocation, currentState));

    auto it = currentState.m_hostGroups.find(name);
    CPPUNIT_ASSERT(it == currentState.m_hostGroups.end());
    
}

void
TESTNAME::test_config_garbage_tests()
{
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(HMConfigParserBase::parseDirectory(garbageLocation, currentState));

}

void
TESTNAME::test_neg_configs()
{
    HMConfigParserYAML parse;

    CPPUNIT_ASSERT(HMConfigParserBase::parseDirectory(garbageLocation, currentState));
    CPPUNIT_ASSERT(parse.parseConfig(wrongConfig, currentState) == 0);
}

void
TESTNAME::test_write_configs()
{
    HMConfigParserYAML parse;
    string configOutputFile = "test.yaml";
    CPPUNIT_ASSERT(parse.parseConfig(fileLocation3, currentState) == 0);
    CPPUNIT_ASSERT(parse.writeConfigs(currentState, configOutputFile));
    HMState newState;
    CPPUNIT_ASSERT(parse.parseConfig(configOutputFile, newState) == 0);
    for (auto it = currentState.m_hostGroups.begin();
            it != currentState.m_hostGroups.end(); ++it)
    {
        auto iit = newState.m_hostGroups.find(it->first);
        CPPUNIT_ASSERT(iit != newState.m_hostGroups.end());
        CPPUNIT_ASSERT(iit->second == it->second);
        const vector<string> *hosts = it->second.getHostList();
        const vector<string> *hosts1 = iit->second.getHostList();
        CPPUNIT_ASSERT_EQUAL(hosts->size(), hosts1->size());
        for (uint64_t i = 0; i < hosts->size(); i++)
        {
            CPPUNIT_ASSERT((*hosts)[i] == (*hosts1)[i]);
        }
    }
    remove(configOutputFile.c_str());
}


void
TESTNAME::test_write_configs1()
{
    HMConfigParserYAML parse;
    string configOutputFile = "test.yaml";
    CPPUNIT_ASSERT(HMConfigParserBase::parseDirectory(folderLocation, currentState) == 0);

    CPPUNIT_ASSERT(parse.writeConfigs(currentState, configOutputFile));
    HMState newState;
    CPPUNIT_ASSERT(parse.parseConfig(configOutputFile, newState) == 0);
    for (auto it = currentState.m_hostGroups.begin();
            it != currentState.m_hostGroups.end(); ++it)
    {
        auto iit = newState.m_hostGroups.find(it->first);
        CPPUNIT_ASSERT(iit != newState.m_hostGroups.end());
        CPPUNIT_ASSERT(iit->second == it->second);
        const vector<string> *hosts = it->second.getHostList();
        const vector<string> *hosts1 = iit->second.getHostList();
        CPPUNIT_ASSERT_EQUAL(hosts->size(), hosts1->size());
        for (uint64_t i = 0; i < hosts->size(); i++)
        {
            CPPUNIT_ASSERT((*hosts)[i] == (*hosts1)[i]);
        }
    }
    remove(configOutputFile.c_str());
}
