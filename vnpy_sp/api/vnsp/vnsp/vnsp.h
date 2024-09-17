#pragma once

#include "stdafx.h"
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>
#include <codecvt>
#include <condition_variable>
#include <locale>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h> 

#include "pybind11/pybind11.h"
#include "sp/spapidll.h"



using namespace std;
using namespace pybind11;


//����ṹ��
struct Task
{
    int task_name;		//�ص��������ƶ�Ӧ�ĳ���
    void* task_data;	//����ָ��
    void* task_error;	//����ָ��
    int task_id;		//����id
    bool task_last;		//�Ƿ�Ϊ��󷵻�
};

class TerminatedError : std::exception
{};

class TaskQueue
{
private:
    queue<Task> queue_;						//��׼�����
    mutex mutex_;							//������
    condition_variable cond_;				//��������

    bool _terminate = false;

public:

    //�����µ�����
    void push(const Task& task)
    {
        unique_lock<mutex > mlock(mutex_);
        queue_.push(task);					//������д�������
        mlock.unlock();						//�ͷ���
        cond_.notify_one();					//֪ͨ���������ȴ����߳�
    }

    //ȡ���ϵ�����
    Task pop()
    {
        unique_lock<mutex> mlock(mutex_);
        cond_.wait(mlock, [&]() {
            return !queue_.empty() || _terminate;
            });				//�ȴ���������֪ͨ
        if (_terminate)
            throw TerminatedError();
        Task task = queue_.front();			//��ȡ�����е����һ������
        queue_.pop();						//ɾ��������
        return task;						//���ظ�����
    }

    void terminate()
    {
        _terminate = true;
        cond_.notify_all();					//֪ͨ���������ȴ����߳�
    }
};

void getLong(const dict &d, const char *key, long *value)
{
    if (d.contains(key))		//����ֵ����Ƿ���ڸü�ֵ
    {
        object o = d[key];		//��ȡ�ü�ֵ
        *value = o.cast<long>();
    }
};


//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getInt(const dict& d, const char* key, int* value)
{
    if (d.contains(key))		//����ֵ����Ƿ���ڸü�ֵ
    {
        object o = d[key];		//��ȡ�ü�ֵ
        *value = o.cast<int>();
    }
};


//���ֵ��л�ȡĳ����ֵ��Ӧ�ĸ�����������ֵ������ṹ������ֵ��
void getDouble(const dict& d, const char* key, double* value)
{
    if (d.contains(key))
    {
        object o = d[key];
        *value = o.cast<double>();
    }
};


//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ�������ֵ������ṹ������ֵ��
void getChar(const dict& d, const char* key, char* value)
{
    if (d.contains(key))
    {
        object o = d[key];
        *value = o.cast<char>();
    }
};


template <size_t size>
using string_literal = char[size];

//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ���������ֵ������ṹ������ֵ��
template <size_t size>
void getString(const pybind11::dict& d, const char* key, string_literal<size>& value)
{
    if (d.contains(key)) 
    {
        object o = d[key];
        string s = o.cast<string>();
        const char* buf = s.c_str();
        strcpy_s(value, buf);
    }
};


//��GBK������ַ���ת��ΪUTF8
inline string toUtf(const string& gb2312)
{
    const static locale loc("zh-CN");

    vector<wchar_t> wstr(gb2312.size());
    wchar_t* wstrEnd = nullptr;
    const char* gbEnd = nullptr;
    mbstate_t state = {};
    int res = use_facet<codecvt<wchar_t, char, mbstate_t> >
        (loc).in(state,
            gb2312.data(), gb2312.data() + gb2312.size(), gbEnd,
            wstr.data(), wstr.data() + wstr.size(), wstrEnd);

    if (codecvt_base::ok == res)
    {
        wstring_convert<codecvt_utf8<wchar_t>> cutf8;
        return cutf8.to_bytes(wstring(wstr.data(), wstrEnd));
    }

    return string();
}


//��װAPI��
class SpApi
{
private:
    bool active = false;                //����״̬

public:
    SpApi();
    ~SpApi();

    //-------------------------------------------------------------------------------------
    //Python�ص�����
    //-------------------------------------------------------------------------------------

    virtual void onLoginReply(long code) {};
    	
    virtual void onConnectedReply(long id,long code){};

	virtual void onApiOrderRequestFailed(const dict &data, int code, char error){};

	virtual void onApiOrderReport(const dict &data){};

	virtual void onApiOrderBeforeSendReport(const dict &data){};

	virtual void onAccountLoginReply(int code, char error){};

	virtual void onAccountLogoutReply(int code, char error){};

	virtual void onAccountInfoPush(const dict &data){};

	virtual void onAccountPositionPush(const dict &data){};

	virtual void onUpdatedAccountPositionPush(const dict &data){};

	virtual void onUpdatedAccountBalancePush(const dict &data){};

	virtual void onApiTradeReport(const dict &data){};

	virtual void onApiPriceUpdate(const dict &data){};

	virtual void onApiTickerUpdate(const dict &data){};

	virtual void onInstrumentListReply(int id,char error){};

	virtual void onApiMMOrderRequestFailed(const dict &data, int code, char error){};

	virtual void onApiLoadTradeReadyPush(const dict &data){};

	virtual void onInstrument(const dict &data){};

 	virtual void onProduct(const dict &data){};

    //-------------------------------------------------------------------------------------
    //Python��������
    //-------------------------------------------------------------------------------------



    void createApi();

    int login(const dict &req);

    int getAPIVersion();

    int loadInstrument();

	void getProduct();
	
	void loadProductInfoListByCode(string code);
	
	void loadProductInfoListByMarket(string code);

	void getProductByCode(string code);

	void subscribeQuote(const dict &req);

	int reqOrderInsert(const dict &req);

	void reqOrderDelete(const dict &req);

	void getAllAccBal(const dict &req);
	
	void getAccInfo(const dict &req);

	void getAllPos(const dict &req);

	void getInstrument();

};


//-------------------------------------------------------------------------------------
//C++�ص�����
//-------------------------------------------------------------------------------------

void SPDLLCALL ONLoginReplyAddr(char *user_id, long ret_code, char *ret_msg);
void SPDLLCALL ONConnectedReplyAddr(long host_type, long con_status);
void SPDLLCALL ONApiOrderRequestFailedAddr(tinyint action, SPApiOrder* order, long err_code, char* err_msg);
void SPDLLCALL ONApiOrderReportAddr(long rec_no, SPApiOrder* order);
void SPDLLCALL ONApiOrderBeforeSendReportAddr(SPApiOrder* order);
void SPDLLCALL ONAccountLoginReplyAddr(char* accNo, long ret_code, char* ret_msg);
void SPDLLCALL ONAccountLogoutReplyAddr(char* accNo, long ret_code, char* ret_msg);
void SPDLLCALL ONAccountInfoPushAddr(SPApiAccInfo* acc_info);

void SPDLLCALL ONAccountPositionPushAddr(SPApiPos* pos);
void SPDLLCALL ONUpdatedAccountPositionPushAddr(SPApiPos* pos);
void SPDLLCALL ONUpdatedAccountBalancePushAddr(SPApiAccBal* acc_bal);
void SPDLLCALL ONApiTradeReportAddr(long rec_no, SPApiTrade* trade);
//void SPDLLCALL ONApiLoadTradeReadyPushAddr(long rec_no, SPApiTrade* trade);
void SPDLLCALL ONApiPriceUpdateAddr(SPApiPrice* price);
void SPDLLCALL ONApiTickerUpdateAddr(SPApiTicker* ticker);
//void SPDLLCALL PswChangeReplyAddr(long ret_code, char* ret_msg);
void SPDLLCALL ONProductListByCodeReplyAddr(long req_id, char *inst_code, bool is_ready, char *ret_msg);
void SPDLLCALL ONInstrumentListReplyAddr(long req_id, bool is_ready, char* ret_msg);
void SPDLLCALL ONBusinessDateReplyAddr(long business_date);
void SPDLLCALL ONApiMMOrderBeforeSendReportAddr(SPApiMMOrder* mm_order);
void SPDLLCALL ONApiMMOrderRequestFailedAddr(SPApiMMOrder* mm_order, long err_code, char* err_msg);
void SPDLLCALL ONApiQuoteRequestReceivedAddr(char* product_code, char buy_sell, long qty);
void SPDLLCALL ONAccountControlReplyAddr(long ret_code, char* ret_msg);


//-------------------------------------------------------------------------------------
//C++��������
//-------------------------------------------------------------------------------------

p_SPAPI_RegisterLoginReply				 SPAPI_RegisterLoginReply;
p_SPAPI_RegisterConnectingReply          SPAPI_RegisterConnectingReply;
p_SPAPI_RegisterOrderReport              SPAPI_RegisterOrderReport;
p_SPAPI_RegisterOrderRequestFailed       SPAPI_RegisterOrderRequestFailed;
p_SPAPI_RegisterOrderBeforeSendReport    SPAPI_RegisterOrderBeforeSendReport;
p_SPAPI_RegisterAccountLoginReply        SPAPI_RegisterAccountLoginReply;
p_SPAPI_RegisterAccountLogoutReply       SPAPI_RegisterAccountLogoutReply;
p_SPAPI_RegisterAccountInfoPush          SPAPI_RegisterAccountInfoPush;
p_SPAPI_RegisterAccountPositionPush      SPAPI_RegisterAccountPositionPush;
p_SPAPI_RegisterUpdatedAccountPositionPush    SPAPI_RegisterUpdatedAccountPositionPush;
p_SPAPI_RegisterUpdatedAccountBalancePush     SPAPI_RegisterUpdatedAccountBalancePush;
p_SPAPI_RegisterTradeReport              SPAPI_RegisterTradeReport;
p_SPAPI_RegisterLoadTradeReadyPush       SPAPI_RegisterLoadTradeReadyPush;
p_SPAPI_RegisterApiPriceUpdate           SPAPI_RegisterApiPriceUpdate;
p_SPAPI_RegisterTickerUpdate             SPAPI_RegisterTickerUpdate;
p_SPAPI_RegisterPswChangeReply           SPAPI_RegisterPswChangeReply;
p_SPAPI_RegisterProductListByCodeReply   SPAPI_RegisterProductListByCodeReply;
p_SPAPI_RegisterInstrumentListReply      SPAPI_RegisterInstrumentListReply;
p_SPAPI_RegisterBusinessDateReply        SPAPI_RegisterBusinessDateReply;
p_SPAPI_RegisterMMOrderRequestFailed         SPAPI_RegisterMMOrderRequestFailed;
p_SPAPI_RegisterMMOrderBeforeSendReport      SPAPI_RegisterMMOrderBeforeSendReport;
p_SPAPI_RegisterQuoteRequestReceivedReport   SPAPI_RegisterQuoteRequestReceivedReport;
p_SPAPI_RegisterAccountControlReply          SPAPI_RegisterAccountControlReply;

p_SPAPI_GetDllVersion      SPAPI_GetDllVersion;
p_SPAPI_Initialize		   SPAPI_Initialize;
p_SPAPI_SetLoginInfo	   SPAPI_SetLoginInfo;
p_SPAPI_Login			   SPAPI_Login;
p_SPAPI_Logout             SPAPI_Logout;
p_SPAPI_AccountLogin        SPAPI_AccountLogin;
p_SPAPI_AccountLogout       SPAPI_AccountLogout;
p_SPAPI_Uninitialize        SPAPI_Uninitialize;

p_SPAPI_AddOrder		   SPAPI_AddOrder;
p_SPAPI_AddInactiveOrder   SPAPI_AddInactiveOrder;
p_SPAPI_ChangeOrder        SPAPI_ChangeOrder;
p_SPAPI_ChangeOrderBy      SPAPI_ChangeOrderBy;
p_SPAPI_DeleteOrderBy      SPAPI_DeleteOrderBy;
p_SPAPI_DeleteAllOrders    SPAPI_DeleteAllOrders;
p_SPAPI_ActivateAllOrders  SPAPI_ActivateAllOrders;
p_SPAPI_InactivateAllOrders  SPAPI_InactivateAllOrders;
p_SPAPI_ActivateOrderBy      SPAPI_ActivateOrderBy;
p_SPAPI_InactivateOrderBy    SPAPI_InactivateOrderBy;
p_SPAPI_GetOrderCount        SPAPI_GetOrderCount;
p_SPAPI_GetOrderByOrderNo    SPAPI_GetOrderByOrderNo;
p_SPAPI_GetActiveOrders      SPAPI_GetActiveOrders;
p_SPAPI_SendMarketMakingOrder  SPAPI_SendMarketMakingOrder;

p_SPAPI_GetPosCount        SPAPI_GetPosCount;
p_SPAPI_GetPosByProduct    SPAPI_GetPosByProduct;
p_SPAPI_GetAllPos          SPAPI_GetAllPos;
p_SPAPI_GetAllPosByArray   SPAPI_GetAllPosByArray;

p_SPAPI_GetTradeCount SPAPI_GetTradeCount;
p_SPAPI_GetAllTrades  SPAPI_GetAllTrades;

p_SPAPI_SubscribePrice            SPAPI_SubscribePrice;
p_SPAPI_SubscribeTicker           SPAPI_SubscribeTicker;
p_SPAPI_GetPriceByCode	          SPAPI_GetPriceByCode;
p_SPAPI_SubscribeQuoteRequest     SPAPI_SubscribeQuoteRequest;
p_SPAPI_SubscribeAllQuoteRequest  SPAPI_SubscribeAllQuoteRequest;


p_SPAPI_ChangePassword       SPAPI_ChangePassword;

p_SPAPI_GetAccInfo           SPAPI_GetAccInfo;
p_SPAPI_GetAccBalCount       SPAPI_GetAccBalCount;
p_SPAPI_GetAccBalByCurrency  SPAPI_GetAccBalByCurrency;
p_SPAPI_GetAllAccBal         SPAPI_GetAllAccBal;

p_SPAPI_GetLoginStatus      SPAPI_GetLoginStatus;
p_SPAPI_GetCcyRateByCcy     SPAPI_GetCcyRateByCcy;
p_SPAPI_SetApiLogPath       SPAPI_SetApiLogPath;

p_SPAPI_GetProductCount           SPAPI_GetProductCount;
p_SPAPI_GetProduct                SPAPI_GetProduct;
p_SPAPI_GetProductByCode          SPAPI_GetProductByCode;
p_SPAPI_LoadProductInfoListByCode SPAPI_LoadProductInfoListByCode;
p_SPAPI_LoadProductInfoListByMarket SPAPI_LoadProductInfoListByMarket;

p_SPAPI_LoadInstrumentList   SPAPI_LoadInstrumentList;
p_SPAPI_GetInstrumentCount   SPAPI_GetInstrumentCount;
p_SPAPI_GetInstrument        SPAPI_GetInstrument;
p_SPAPI_GetInstrumentByCode  SPAPI_GetInstrumentByCode;

p_SPAPI_SetLanguageId        SPAPI_SetLanguageId;

p_SPAPI_GetAllTradesByArray  SPAPI_GetAllTradesByArray;
p_SPAPI_GetOrdersByArray     SPAPI_GetOrdersByArray;
p_SPAPI_GetAllAccBalByArray  SPAPI_GetAllAccBalByArray;
p_SPAPI_GetInstrumentByArray SPAPI_GetInstrumentByArray;
p_SPAPI_GetProductByArray    SPAPI_GetProductByArray;
p_SPAPI_SendAccControl       SPAPI_SendAccControl;


//-------------------------------------------------------------------------------------
//C++ȫ�ֶ���
//-------------------------------------------------------------------------------------

SpApi* api;
#pragma warning(disable:4996)
