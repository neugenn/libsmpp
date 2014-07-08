#ifndef PDUHEADERTESTS_H_
#define PDUHEADERTESTS_H_

#include "PduHeader.h"
#include <cppunit/extensions/HelperMacros.h>

class PduHeaderTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PduHeaderTests);
    CPPUNIT_TEST(testEmptyHeader);
    CPPUNIT_TEST(testData);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testCommandLen);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCommandStatus);
    CPPUNIT_TEST(testSequence);
    CPPUNIT_TEST_SUITE_END();

    public:
    virtual void setUp();
    virtual void tearDown();
    void testEmptyHeader();
    void testData();
    void testSize();
    void testOperatorEqual();
    void testOperatorNotEqual();
    void testCommandLen();
    void testCommandId();
    void testCommandStatus();
    void testSequence();

    private:
    SMPP::PduHeader* pHeader_;
};

CPPUNIT_TEST_SUITE_REGISTRATION(PduHeaderTests);

using SMPP::PduHeader;

void PduHeaderTests::setUp()
{
    pHeader_ = new PduHeader;
    CPPUNIT_ASSERT(NULL != pHeader_);
}

void PduHeaderTests::tearDown()
{
    delete pHeader_;
}

void PduHeaderTests::testData()
{
    std::stringstream s;
    s << *pHeader_;
    CPPUNIT_ASSERT_EQUAL(std::string("00000010000000010000000400000004"), s.str());
}

void PduHeaderTests::testSize()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(16), pHeader_->Size());
}

void PduHeaderTests::testOperatorEqual()
{
    PduHeader h1;
    PduHeader h2;
    CPPUNIT_ASSERT_EQUAL(h1, h2);
}

void PduHeaderTests::testOperatorNotEqual()
{
    PduHeader h1;
    PduHeader h2;
    h2.SetSequenceNumber(12);

    CPPUNIT_ASSERT(h1 != h2);
}

void PduHeaderTests::testEmptyHeader()
{
    PduHeader h;
    std::stringstream s;
    s << h;
    CPPUNIT_ASSERT_EQUAL(std::string("00000000000000000000000000000000"), s.str());
}

void PduHeaderTests::testCommandLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(0), pHeader_->CommandLength());
}

void PduHeaderTests::testCommandId()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::BIND_RECEIVER, pHeader_->CommandId());
}

void PduHeaderTests::testCommandStatus()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::ESME_ROK, pHeader_->CommandStatus());
}

void PduHeaderTests::testSequence()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(0x00000000), pHeader_->SequenceNumber());
}

#endif // PDUHEADERTESTS_H_
