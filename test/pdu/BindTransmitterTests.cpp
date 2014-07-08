#ifndef BINDTRANSMITTERTESTS_H_
#define BINDTRANSMITTERTESTS_H_

#include <cppunit/extensions/HelperMacros.h>
#include <iomanip>
#include "BindTransmitter.h"

class TestingBindTransmitter : public SMPP::BindTransmitter
{
public:
    TestingBindTransmitter() : SMPP::BindTransmitter()
    {}

private:
    virtual void GetFormattedContent(std::string& s) const
    {
        const SMPP::value_t pduSize = this->Size();
        unsigned char* pdu = new unsigned char[pduSize];
        memcpy(pdu, this->Data(), pduSize);

        std::stringstream str;
        for (SMPP::value_t i = 0; i < pduSize; ++i)
        {
            str << std::setfill('0') << std::setw(2) << std::uppercase << std::hex;
            str << static_cast<unsigned int>(pdu[i]);
        }
        delete [] pdu;

        s = str.str();
    }
};

class BindTransmitterTests : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(BindTransmitterTests);
    CPPUNIT_TEST(testSystemIdLen);
    CPPUNIT_TEST(testPasswordLen);
    CPPUNIT_TEST(testSystemTypeLen);
    CPPUNIT_TEST(testAddressRangeLen);
    CPPUNIT_TEST(testMinPduSize);
    CPPUNIT_TEST(testMaxPduSize);
    CPPUNIT_TEST(testCreateEmpty);
    CPPUNIT_TEST(testCreateWithNullData);
    CPPUNIT_TEST(testCreateWithShortCommandLen);
//    CPPUNIT_TEST(testCreateWithLongCommandLen);
    CPPUNIT_TEST(testCreateWithInvalidCommandId);
    CPPUNIT_TEST(testCommandId);
    CPPUNIT_TEST(testCopyConstruction);
    CPPUNIT_TEST(testAssignment);
    CPPUNIT_TEST_SUITE_END();

	public:
	virtual void setUp();
    virtual void tearDown();
    void testSystemIdLen();
    void testPasswordLen();
    void testSystemTypeLen();
    void testAddressRangeLen();
    void testMinPduSize();
    void testMaxPduSize();
    void testCreateEmpty();
    void testCreateWithNullData();
    void testCommandId();
    void testCreateWithInvalidCommandId();
    void testCreateWithShortCommandLen();
//    void testCreateWithLongCommandLen();
    void testCopyConstruction();
    void testAssignment();

    private:
    SMPP::BindTransmitter* pPdu_;

    public:
    static const unsigned char ValidBindTransmitterBody[33];
};

const unsigned char BindTransmitterTests::ValidBindTransmitterBody[33] =
{
    0x73, 0x6d, 0x73, 0x00,  // system_id
    0x70, 0x61, 0x31, 0x00, // password
    0x4f, 0x54, 0x41, 0x00, // system_type
    0x34, // interface_version
    0x01, // addr_ton
    0x01, // addr_npi
    0x01, 0x00 // address_range
};


CPPUNIT_TEST_SUITE_REGISTRATION(BindTransmitterTests);

void BindTransmitterTests::setUp()
{
    SMPP::PduHeader h;
    h.SetCommandId(SMPP::BIND_TRANSMITTER);
    h.SetCommandLength(33);
    pPdu_ = new SMPP::BindTransmitter(h, &ValidBindTransmitterBody[0]);
    CPPUNIT_ASSERT(NULL != pPdu_);
}

void BindTransmitterTests::tearDown()
{
    delete pPdu_;
}

void BindTransmitterTests::testSystemIdLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(16), SMPP::BindTransmitter::SYSTEM_ID_MAX_LEN);
}

void BindTransmitterTests::testPasswordLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(9), SMPP::BindTransmitter::PASSWORD_MAX_LEN);
}

void BindTransmitterTests::testSystemTypeLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(13), SMPP::BindTransmitter::SYSTEM_TYPE_MAX_LEN);
}

void BindTransmitterTests::testAddressRangeLen()
{
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(41), SMPP::BindTransmitter::ADDRESS_RANGE_MAX_LEN);
}

void BindTransmitterTests::testMinPduSize()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(23), t.MinSize());
}

void BindTransmitterTests::testMaxPduSize()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(SMPP::value_t(98), t.MaxSize());
}

void BindTransmitterTests::testCreateEmpty()
{
    TestingBindTransmitter t;

    std::stringstream s;
    s << t;
    CPPUNIT_ASSERT_EQUAL(std::string("0000001700000002000000000000000000000000000000"), s.str());
}

void BindTransmitterTests::testCreateWithNullData()
{
    SMPP::PduHeader h;
    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(h, NULL), std::invalid_argument);
}

void BindTransmitterTests::testCommandId()
{
    SMPP::BindTransmitter t;
    CPPUNIT_ASSERT_EQUAL(SMPP::BIND_TRANSMITTER, t.CommandId());
}

void BindTransmitterTests::testCreateWithInvalidCommandId()
{
    const unsigned char Body[] =
    {
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    SMPP::PduHeader h;
    h.SetCommandId(SMPP::BIND_RECEIVER);
    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(h, &Body[0]), std::invalid_argument);
}

void BindTransmitterTests::testCreateWithShortCommandLen()
{
    const unsigned char Data[] =
    {
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    SMPP::PduHeader h;
    h.SetCommandId(SMPP::BIND_TRANSMITTER);
    h.SetCommandLength(16);
    SMPP::BindTransmitter t(h, &Data[0]);
    std::cout << t << std::endl;
    CPPUNIT_ASSERT_EQUAL(false, t.IsValid());
}

/*
void BindTransmitterTests::testCreateWithLongCommandLen()
{
    const unsigned char InvalidLongCommandLenData[] =
    {
        0x00, 0x00, 0x00, 0xFF, // command_length
        0x00, 0x00, 0x00, 0x02, // command_id
        0x00, 0x00, 0x00, 0x00, // command_status
        0x00, 0x00, 0x00, 0x01, // sequence_number
        0x73, 0x6d, 0x73, 0x00,  // system_id
        0x70, 0x61, 0x31, 0x00, // password
        0x4f, 0x54, 0x41, 0x00, // system_type
        0x34, // interface_version
        0x01, // addr_ton
        0x01, // addr_npi
        0x01, 0x00 // address_range
        };

    CPPUNIT_ASSERT_THROW(new SMPP::BindTransmitter(&InvalidLongCommandLenData[0], sizeof(InvalidLongCommandLenData)), std::invalid_argument);
}
*/

void BindTransmitterTests::testCopyConstruction()
{
    SMPP::BindTransmitter t1(*pPdu_);
    SMPP::BindTransmitter t2(t1);
    CPPUNIT_ASSERT_EQUAL(t1, t2);
}

void BindTransmitterTests::testAssignment()
{
    SMPP::BindTransmitter t1(*pPdu_);
    SMPP::BindTransmitter t2;
    t2 = t1;

    CPPUNIT_ASSERT_EQUAL(t1, t2);
}
#endif // BINDTRANSMITTERTESTS_H_
