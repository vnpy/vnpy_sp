#include "stdafx.h"
#include "vnsp.h"




///-------------------------------------------------------------------------------------
///C++的回调函数
///-------------------------------------------------------------------------------------
/// 
SpApi::SpApi()
{
    api = this;
};

SpApi::~SpApi() {
    api = NULL;

};

void SPDLLCALL ONLoginReplyAddr(char *user_id, long ret_code, char *ret_msg)
{
    gil_scoped_acquire acquire;
	api->onLoginReply(ret_code);
};

void SPDLLCALL ONConnectedReplyAddr(long host_type,long con_status)//---1
{	
	gil_scoped_acquire acquire;
	api->onConnectedReply(host_type,con_status);
};

void SPDLLCALL ONAccountInfoPushAddr(SPApiAccInfo* acc_info)
{
	gil_scoped_acquire acquire;
	// cout << "OnAccountInfoPush" << endl;
	dict data;
	if (acc_info)
	{
		data["NAV"]=acc_info->NAV;
		data["BuyingPower"]=acc_info->BuyingPower;
		data["CashBal"]=acc_info->CashBal;
		data["MarginCall"]=acc_info->MarginCall;
		data["CommodityPL"]=acc_info->CommodityPL;
		data["LockupAmt"]=acc_info->LockupAmt;
		data["CreditLimit"]=acc_info->CreditLimit;
		data["MaxMargin"]=acc_info->MaxMargin;
		data["MaxLoanLimit"]=acc_info->MaxLoanLimit;
		data["TradingLimit"]=acc_info->TradingLimit;
		data["RawMargin"]=acc_info->RawMargin;
		data["IMargin"]=acc_info->IMargin;
		data["MMargin"]=acc_info->MMargin;
		data["TodayTrans"]=acc_info->TodayTrans;
		data["LoanLimit"]=acc_info->LoanLimit;
		data["TotalFee"]=acc_info->TotalFee;
		// data["LoanToMR"]=acc_info->LoanToMR;
		// data["LoanToMV"]=acc_info->LoanToMV;
		// data["AccName"]=acc_info->AccName;
		// data["BaseCcy"]=acc_info->BaseCcy;
		// data["MarginClass"]=acc_info->MarginClass;

		// data["TradeClass"]=acc_info->TradeClass;
		data["ClientId"]=acc_info->ClientId;
		// data["AEId"]=acc_info->AEId;
		// data["AccType"]=acc_info->AccType;
		// data["CtrlLevel"]=acc_info->CtrlLevel;
		// data["Active"]=acc_info->Active;
		// data["MarginPeriod"]=acc_info->MarginPeriod;
	}
	api->onAccountInfoPush(data);
};

void SPDLLCALL ONApiOrderRequestFailedAddr(tinyint action, SPApiOrder* order, long err_code, char* err_msg)
{
	gil_scoped_acquire acquire;
	cout << "OnApiOrderRequestFailed" << endl;
	dict data;
	if (order)
	{
		data["Price"] = order->Price;
		data["StopLevel"] = order->StopLevel;
		data["UpLevel"] = order->UpLevel;
		data["UpPrice"] = order->UpPrice;
		data["DownLevel"] = order->DownLevel;
		data["DownPrice"] = order->DownPrice;
		data["ExtOrderNo"] = order->ExtOrderNo;
		data["IntOrderNo"] = order->IntOrderNo;
		data["Qty"] = order->Qty;
		data["TradedQty"] = order->TradedQty;
		data["TotalQty"] = order->TotalQty;
		data["ValidTime"] = order->ValidTime;
		data["SchedTime"] = order->SchedTime;
		data["TimeStamp"] = order->TimeStamp;
		data["OrderOptions"] = order->OrderOptions;
		data["AccNo"] = order->AccNo;
		data["ProdCode"] = order->ProdCode;
		data["Initiator"] = order->Initiator;
		data["BuySell"] = order->BuySell;
		data["StopType"] = order->StopType;
		data["OpenClose"] = order->OpenClose;
		data["CondType"] = order->CondType;
		data["OrderType"] = order->OrderType;
		data["ValidType"] = order->ValidType;
		data["Status"] = order->Status;
		data["DecInPrice"] = order->DecInPrice;
		data["OrderAction"] = order->OrderAction;
		data["UpdateTime"] = order->UpdateTime;
		data["UpdateSeqNo"] = order->UpdateSeqNo;
	}

	api->onApiOrderRequestFailed(data, err_code, *err_msg);
};

void SPDLLCALL ONApiOrderReportAddr(long rec_no, SPApiOrder* order)
{
	gil_scoped_acquire acquire;
	// cout << "OnApiOrderReport" << endl;
	dict data;

	if (order)
	{
		data["Price"] = order->Price;
		data["StopLevel"] = order->StopLevel;
		data["UpLevel"] = order->UpLevel;
		data["UpPrice"] = order->UpPrice;
		data["DownLevel"] = order->DownLevel;
		data["DownPrice"] = order->DownPrice;
		data["ExtOrderNo"] = order->ExtOrderNo;
		data["IntOrderNo"] = order->IntOrderNo;
		data["Qty"] = order->Qty;
		data["TradedQty"] = order->TradedQty;
		data["TotalQty"] = order->TotalQty;
		data["ValidTime"] = order->ValidTime;
		data["SchedTime"] = order->SchedTime;
		data["TimeStamp"] = order->TimeStamp;
		data["OrderOptions"] = order->OrderOptions;
		data["AccNo"] = order->AccNo;
		data["ProdCode"] = order->ProdCode;
		data["Initiator"] = order->Initiator;
		data["BuySell"] = order->BuySell;
		data["StopType"] = order->StopType;
		data["OpenClose"] = order->OpenClose;
		data["CondType"] = order->CondType;
		data["OrderType"] = order->OrderType;
		data["ValidType"] = order->ValidType;
		data["Status"] = order->Status;
		data["DecInPrice"] = order->DecInPrice;
		data["OrderAction"] = order->OrderAction;
		data["UpdateTime"] = order->UpdateTime;
		data["UpdateSeqNo"] = order->UpdateSeqNo;
		data["ClOrderId"]=order->ClOrderId;
	}

	api->onApiOrderReport(data);
};

void SPDLLCALL ONApiOrderBeforeSendReportAddr(SPApiOrder* order)
{
	gil_scoped_acquire acquire;
//	cout << "OnApiOrderBeforeSendReport" << endl;
	dict data;

	if (order)
	{
		data["Price"] = order->Price;
		data["StopLevel"] = order->StopLevel;
		data["UpLevel"] = order->UpLevel;
		data["UpPrice"] = order->UpPrice;
		data["DownLevel"] = order->DownLevel;
		data["DownPrice"] = order->DownPrice;
		data["ExtOrderNo"] = order->ExtOrderNo;
		data["IntOrderNo"] = order->IntOrderNo;
		data["Qty"] = order->Qty;
		data["TradedQty"] = order->TradedQty;
		data["TotalQty"] = order->TotalQty;
		data["ValidTime"] = order->ValidTime;
		data["SchedTime"] = order->SchedTime;
		data["TimeStamp"] = order->TimeStamp;
		data["OrderOptions"] = order->OrderOptions;
		data["AccNo"] = order->AccNo;
		data["ProdCode"] = order->ProdCode;
		data["Initiator"] = order->Initiator;
		data["BuySell"] = order->BuySell;
		data["StopType"] = order->StopType;
		data["OpenClose"] = order->OpenClose;
		data["CondType"] = order->CondType;
		data["OrderType"] = order->OrderType;
		data["ValidType"] = order->ValidType;
		data["Status"] = order->Status;
		data["DecInPrice"] = order->DecInPrice;
		data["OrderAction"] = order->OrderAction;
		data["UpdateTime"] = order->UpdateTime;
		data["UpdateSeqNo"] = order->UpdateSeqNo;
	}
	
	api->onApiOrderBeforeSendReport(data);
};


void SPDLLCALL ONAccountLoginReplyAddr(char *accNo, long ret_code, char* ret_msg)
{
	gil_scoped_acquire acquire;
	//cout << "OnAccountLoginReply" << endl;
	api->onAccountLoginReply(ret_code,*ret_msg);
};

void SPDLLCALL ONAccountLogoutReplyAddr(char *accNo, long ret_code, char* ret_msg)
{
	gil_scoped_acquire acquire;
	//cout << "OnAccountLogoutReply" << endl;
	api->onAccountLogoutReply(ret_code,*ret_msg);
};

void SPDLLCALL ONAccountPositionPushAddr(SPApiPos* pos)
{
	gil_scoped_acquire acquire;
	// cout << "OnAccountPositionPush" << endl;
	dict data;

	if (pos)
	{
		data["Qty"]=pos->Qty;
		data["DepQty"]=pos->DepQty;
		data["LongQty"]=pos->LongQty;
		data["ShortQty"]=pos->ShortQty;
		data["TotalAmt"]=pos->TotalAmt;
		data["DepTotalAmt"]=pos->DepTotalAmt;
		data["LongTotalAmt"]=pos->LongTotalAmt;
		data["ShortTotalAmt"]=pos->ShortTotalAmt;
		data["PLBaseCcy"]=pos->PLBaseCcy;
		data["PL"]=pos->PL;
		data["ExchangeRate"]=pos->ExchangeRate;
		data["AccNo"]=pos->AccNo;
		data["ProdCode"]=pos->ProdCode;
		data["LongShort"]=pos->LongShort;
		data["DecInPrice"]=pos->DecInPrice;
	
	
	}
	api->onAccountPositionPush(data);
};

void SPDLLCALL ONUpdatedAccountPositionPushAddr(SPApiPos* pos)
{
	gil_scoped_acquire acquire;
	//cout << "OnUpdatedAccountPositionPush" << endl;
	dict data;

	if (pos)
	{
		data["Qty"]=pos->Qty;
		data["DepQty"]=pos->DepQty;
		data["LongQty"]=pos->LongQty;
		data["ShortQty"]=pos->ShortQty;
		data["TotalAmt"]=pos->TotalAmt;
		data["DepTotalAmt"]=pos->DepTotalAmt;
		data["LongTotalAmt"]=pos->LongTotalAmt;
		data["ShortTotalAmt"]=pos->ShortTotalAmt;
		data["PLBaseCcy"]=pos->PLBaseCcy;
		data["PL"]=pos->PL;
		data["ExchangeRate"]=pos->ExchangeRate;
		data["AccNo"]=pos->AccNo;
		data["ProdCode"]=pos->ProdCode;
		data["LongShort"]=pos->LongShort;
		data["DecInPrice"]=pos->DecInPrice;
	}
	
	api->onUpdatedAccountPositionPush(data);
};

void SPDLLCALL ONUpdatedAccountBalancePushAddr(SPApiAccBal* acc_bal)
{
	gil_scoped_acquire acquire;
	//cout << "OnUpdatedAccountBalancePush" << endl;
	dict data;

	if (acc_bal)
	{			
	data["CashBf"]=acc_bal->CashBf;
	data["TodayCash"]=acc_bal->TodayCash;
	data["NotYetValue"]=acc_bal->NotYetValue;
	data["Unpresented"]=acc_bal->Unpresented;
	data["TodayOut"]=acc_bal->TodayOut;
	data["Ccy"]=acc_bal->Ccy;
	}
	api->onUpdatedAccountBalancePush(data);
};

void SPDLLCALL ONApiTradeReportAddr(long rec_no, SPApiTrade* trade)
{
	gil_scoped_acquire acquire;
	cout << "OnApiTradeReport" << endl;
	dict data;

	if (trade)
	{
		data["RecNo"]=trade->RecNo;
		data["Price"]=trade->Price;
		data["TradeNo"]=trade->TradeNo;
		data["ExtOrderNo"]=trade->ExtOrderNo;
		data["IntOrderNo"]=trade->IntOrderNo;
		data["Qty"]=trade->Qty;
		data["TradeDate"]=trade->TradeDate;
		data["TradeTime"]=trade->TradeTime;
		data["AccNo"]=trade->AccNo;
		data["ProdCode"]=trade->ProdCode;
		data["Initiator"]=trade->Initiator;
		data["GatewayCode"]=trade->GatewayCode;
		data["ClOrderId"]=trade->ClOrderId;
		data["BuySell"]=trade->BuySell;
		data["OpenClose"]=trade->OpenClose;
		data["Status"]=trade->Status;
		data["DecInPrice"]=trade->DecInPrice;
		data["OrderPrice"]=trade->OrderPrice;
		data["TradeRef"]=trade->TradeRef;
		data["TotalQty"]=trade->TotalQty;
		data["RemainingQty"]=trade->RemainingQty;
		data["TradedQty"]=trade->TradedQty;
		data["AvgTradedPrice"]=trade->AvgTradedPrice;	
	}

	api->onApiTradeReport(data);

};



void SPDLLCALL ONApiPriceUpdateAddr(SPApiPrice* price)
{
	gil_scoped_acquire acquire;
	// cout << "OnApiPriceUpdate" << endl;
	dict data;

	if (price)
	{
	data["QBidPrice0"]=price->Bid[0];
	data["QBidPrice1"]=price->Bid[1];
	data["QBidPrice2"]=price->Bid[2];
	data["QBidPrice3"]=price->Bid[3];
	data["QBidPrice4"]=price->Bid[4];
	data["QBidQty0"]=price->BidQty[0];
	data["QBidQty1"]=price->BidQty[1];
	data["QBidQty2"]=price->BidQty[2];
	data["QBidQty3"]=price->BidQty[3];
	data["QBidQty4"]=price->BidQty[4];

	data["QAskPrice0"]=price->Ask[0];
	data["QAskPrice1"]=price->Ask[1];
	data["QAskPrice2"]=price->Ask[2];
	data["QAskPrice3"]=price->Ask[3];
	data["QAskPrice4"]=price->Ask[4];
	data["QAskQty0"]=price->AskQty[0];
	data["QAskQty1"]=price->AskQty[1];
	data["QAskQty2"]=price->AskQty[2];
	data["QAskQty3"]=price->AskQty[3];
	data["QAskQty4"]=price->AskQty[4];

	data["Last"]=price->Last[0];
	data["volume"]=price->LastQty[0];

	data["Equil"]=price->Equil;
	data["Open"]=price->Open;
	data["High"]=price->High;
	data["Low"]=price->Low;
	data["Close"]=price->Close;
	data["CloseDate"]=price->CloseDate;
	data["TurnoverVol"]=price->TurnoverVol;
	data["TurnoverAmt"]=price->TurnoverAmt;
	data["OpenInt"]=price->OpenInt;
	data["ProdCode"]=price->ProdCode;
	data["ProdName"]=price->ProdName;
	data["DecInPrice"]=price->DecInPrice;
	data["ExStateNo"]=price->ExStateNo;
	data["TradeStateNo"]=price->TradeStateNo;
	data["Suspend"]=price->Suspend;
	data["ExpiryYMD"]=price->ExpiryYMD;
	data["ContractYMD"]=price->ContractYMD;
	data["Timestamp"]=price->Timestamp;	
	}
	api->onApiPriceUpdate(data);

};

void SPDLLCALL ONApiTickerUpdateAddr(SPApiTicker* ticker)
{
	gil_scoped_acquire acquire;
	cout << "OnApiTickerUpdate" << endl;
	dict data;

	if (ticker)
	{
	data["Price"]=ticker->Price;
	data["Qty"]=ticker->Qty;
	data["TickerTime"]=ticker->TickerTime;
	data["DealSrc"]=ticker->DealSrc;
	data["ProdCode"]=ticker->ProdCode;
	data["DecInPrice"]=ticker->DecInPrice;	

	api->onApiTickerUpdate(data);
	}

};

void SPDLLCALL ONProductListByCodeReplyAddr(long req_id, char *inst_code, bool is_ready, char *ret_msg)
{
	gil_scoped_acquire acquire;
	printf("Load Product List(inst code:%s):%s. Ret Msg:%s [Req Id: %d]\n", inst_code, is_ready?"Ok":"No", ret_msg, req_id);
}



void SPDLLCALL ONInstrumentListReplyAddr(long req_id, bool is_ready, char *ret_msg)
{
	gil_scoped_acquire acquire;
	printf("Load Instrument:%s. Ret Msg:%s [Req Id: %d]\n",is_ready?"Ok":"No", ret_msg, req_id);
	//api->onInstrument(req_id,*ret_msg);
};

void SPDLLCALL ONBusinessDateReplyAddr(long business_date)
{
	gil_scoped_acquire acquire;
    struct tm *tblock;
    time_t TheTime = business_date;
    tblock = localtime(&TheTime);
    cout <<"Business Date: "<< business_date << "[" << tblock->tm_year+1900 << "-" << tblock->tm_mon+1 << "-" << tblock->tm_mday << "]" << endl;
};

void SPDLLCALL ONApiMMOrderBeforeSendReportAddr(SPApiMMOrder *mm_order)
{
	gil_scoped_acquire acquire;
	cout << "OnApiMMOrderBeforeSendReport" << endl;
};

void SPDLLCALL ONApiMMOrderRequestFailedAddr(SPApiMMOrder *mm_order, long err_code, char *err_msg)
{
	gil_scoped_acquire acquire;
	cout << "OnApiMMOrderRequestFailed" << endl;
	dict data;

	if (mm_order)
	{
	data["BidExtOrderNo"]=mm_order->BidExtOrderNo;
	data["AskExtOrderNo"]=mm_order->AskExtOrderNo;
	data["BidAccOrderNo"]=mm_order->BidAccOrderNo;
	data["AskAccOrderNo"]=mm_order->AskAccOrderNo;
	data["BidPrice"]=mm_order->BidPrice;
	data["AskPrice"]=mm_order->AskPrice;
	data["BidQty"]=mm_order->BidQty;
	data["AskQty"]=mm_order->AskQty;
	data["SpecTime"]=mm_order->SpecTime;
	data["OrderOptions"]=mm_order->OrderOptions;
	data["ProdCode"]=mm_order->ProdCode;
	data["AccNo"]=mm_order->AccNo;
	data["ClOrderId"]=mm_order->ClOrderId;
	data["OrigClOrdId"]=mm_order->OrigClOrdId;
	data["OrderType"]=mm_order->OrderType;
	data["ValidType"]=mm_order->ValidType;
	data["DecInPrice"]=mm_order->DecInPrice;
	}
	api->onApiMMOrderRequestFailed(data,err_code,*err_msg);

};

void SPDLLCALL ONApiQuoteRequestReceivedAddr(char *product_code, char buy_sell, long qty)
{
	gil_scoped_acquire acquire;
	cout << "OnApiQuoteRequestReceived" << endl;
};

void SPDLLCALL ONAccountControlReplyAddr(long ret_code, char *ret_msg)
{
	gil_scoped_acquire acquire;
	cout << "OnApiAccountControlReply" << endl;
};







///-------------------------------------------------------------------------------------
///C++的主动函数
///-------------------------------------------------------------------------------------

void SpApi::createApi()
{
    //需要将如下dll拷贝到当前目录:
    //libeay32.dll libssl32.dll msvcp100.dll msvcp120.dll msvcr100.dll msvcr120.dll spapidllm64.dll spapidllm64.lib ssleay32.dll
    TCHAR chCurDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,chCurDir);
    cout<<"DIR: "<< chCurDir <<endl;
    HINSTANCE hInst = LoadLibrary("spapidllm64.dll");
    //std::cout<<GetLastError()<<endl;
    cout<<"create api "<< hInst <<endl;

    if (hInst != NULL)
    {
        //加载功能调用主动函数
        cout<<"start load function in spapi"<<endl;
        SPAPI_Initialize = (p_SPAPI_Initialize)GetProcAddress(hInst, "SPAPI_Initialize");
		SPAPI_SetLoginInfo = (p_SPAPI_SetLoginInfo)GetProcAddress(hInst, "SPAPI_SetLoginInfo");
		SPAPI_Login = (p_SPAPI_Login)GetProcAddress(hInst, "SPAPI_Login");
		SPAPI_Logout = (p_SPAPI_Logout)GetProcAddress(hInst, "SPAPI_Logout");	
		SPAPI_AccountLogin  = (p_SPAPI_AccountLogin)GetProcAddress(hInst, "SPAPI_AccountLogin");
		SPAPI_AccountLogout = (p_SPAPI_AccountLogout)GetProcAddress(hInst, "SPAPI_AccountLogout");
		SPAPI_AddOrder = (p_SPAPI_AddOrder)GetProcAddress(hInst, "SPAPI_AddOrder");
		SPAPI_AddInactiveOrder = (p_SPAPI_AddInactiveOrder)GetProcAddress(hInst, "SPAPI_AddInactiveOrder");
		SPAPI_ChangeOrder = (p_SPAPI_ChangeOrder)GetProcAddress(hInst, "SPAPI_ChangeOrder");
		SPAPI_ChangeOrderBy = (p_SPAPI_ChangeOrderBy)GetProcAddress(hInst, "SPAPI_ChangeOrderBy");
		SPAPI_DeleteOrderBy = (p_SPAPI_DeleteOrderBy)GetProcAddress(hInst, "SPAPI_DeleteOrderBy");
		SPAPI_DeleteAllOrders = (p_SPAPI_DeleteAllOrders)GetProcAddress(hInst, "SPAPI_DeleteAllOrders");
		SPAPI_ActivateAllOrders = (p_SPAPI_ActivateAllOrders)GetProcAddress(hInst, "SPAPI_ActivateAllOrders");
		SPAPI_InactivateAllOrders = (p_SPAPI_InactivateAllOrders)GetProcAddress(hInst, "SPAPI_InactivateAllOrders");
		SPAPI_ActivateOrderBy = (p_SPAPI_ActivateOrderBy)GetProcAddress(hInst, "SPAPI_ActivateOrderBy");
		SPAPI_InactivateOrderBy = (p_SPAPI_InactivateOrderBy)GetProcAddress(hInst, "SPAPI_InactivateOrderBy");
		SPAPI_GetOrderCount = (p_SPAPI_GetOrderCount)GetProcAddress(hInst, "SPAPI_GetOrderCount");
		SPAPI_GetOrderByOrderNo = (p_SPAPI_GetOrderByOrderNo)GetProcAddress(hInst, "SPAPI_GetOrderByOrderNo");
		SPAPI_GetActiveOrders = (p_SPAPI_GetActiveOrders)GetProcAddress(hInst, "SPAPI_GetActiveOrders"); 
		SPAPI_SendMarketMakingOrder = (p_SPAPI_SendMarketMakingOrder)GetProcAddress(hInst, "SPAPI_SendMarketMakingOrder");
		SPAPI_GetPosCount = (p_SPAPI_GetPosCount)GetProcAddress(hInst, "SPAPI_GetPosCount"); 
		SPAPI_GetPosByProduct = (p_SPAPI_GetPosByProduct)GetProcAddress(hInst, "SPAPI_GetPosByProduct");
		SPAPI_GetAllPos = (p_SPAPI_GetAllPos)GetProcAddress(hInst, "SPAPI_GetAllPos");
		SPAPI_GetAllPosByArray = (p_SPAPI_GetAllPosByArray)GetProcAddress(hInst, "SPAPI_GetAllPosByArray");
		SPAPI_GetAccInfo = (p_SPAPI_GetAccInfo)GetProcAddress(hInst, "SPAPI_GetAccInfo");
		SPAPI_GetAccBalCount = (p_SPAPI_GetAccBalCount)GetProcAddress(hInst, "SPAPI_GetAccBalCount"); 
		SPAPI_GetAccBalByCurrency = (p_SPAPI_GetAccBalByCurrency)GetProcAddress(hInst, "SPAPI_GetAccBalByCurrency");
		SPAPI_GetAllAccBal = (p_SPAPI_GetAllAccBal)GetProcAddress(hInst, "SPAPI_GetAllAccBal");
		SPAPI_GetTradeCount = (p_SPAPI_GetTradeCount)GetProcAddress(hInst, "SPAPI_GetTradeCount"); 
		SPAPI_GetAllTrades  = (p_SPAPI_GetAllTrades)GetProcAddress(hInst, "SPAPI_GetAllTrades"); 
		SPAPI_SubscribePrice = (p_SPAPI_SubscribePrice)GetProcAddress(hInst, "SPAPI_SubscribePrice"); 
		SPAPI_SubscribeTicker = (p_SPAPI_SubscribeTicker)GetProcAddress(hInst, "SPAPI_SubscribeTicker"); 
		SPAPI_GetPriceByCode = (p_SPAPI_GetPriceByCode)GetProcAddress(hInst, "SPAPI_GetPriceByCode");
		SPAPI_SubscribeQuoteRequest = (p_SPAPI_SubscribeQuoteRequest)GetProcAddress(hInst, "SPAPI_SubscribeQuoteRequest");
		SPAPI_SubscribeAllQuoteRequest = (p_SPAPI_SubscribeAllQuoteRequest)GetProcAddress(hInst, "SPAPI_SubscribeAllQuoteRequest");
		SPAPI_ChangePassword = (p_SPAPI_ChangePassword)GetProcAddress(hInst, "SPAPI_ChangePassword");
		SPAPI_GetLoginStatus = (p_SPAPI_GetLoginStatus)GetProcAddress(hInst, "SPAPI_GetLoginStatus");
		SPAPI_GetCcyRateByCcy = (p_SPAPI_GetCcyRateByCcy)GetProcAddress(hInst, "SPAPI_GetCcyRateByCcy");
		SPAPI_SetApiLogPath = (p_SPAPI_SetApiLogPath)GetProcAddress(hInst, "SPAPI_SetApiLogPath");		
		SPAPI_LoadProductInfoListByMarket = (p_SPAPI_LoadProductInfoListByMarket)GetProcAddress(hInst, "SPAPI_LoadProductInfoListByMarket");
		SPAPI_LoadProductInfoListByCode =(p_SPAPI_LoadProductInfoListByCode)GetProcAddress(hInst, "SPAPI_LoadProductInfoListByCode");
		SPAPI_GetProductCount  = (p_SPAPI_GetProductCount)GetProcAddress(hInst, "SPAPI_GetProductCount");
		SPAPI_GetProduct  = (p_SPAPI_GetProduct)GetProcAddress(hInst, "SPAPI_GetProduct");
		SPAPI_GetProductByCode  = (p_SPAPI_GetProductByCode)GetProcAddress(hInst, "SPAPI_GetProductByCode");
		SPAPI_LoadInstrumentList  = (p_SPAPI_LoadInstrumentList)GetProcAddress(hInst, "SPAPI_LoadInstrumentList");
		SPAPI_GetInstrumentCount = (p_SPAPI_GetInstrumentCount)GetProcAddress(hInst, "SPAPI_GetInstrumentCount");
		SPAPI_GetInstrument = (p_SPAPI_GetInstrument)GetProcAddress(hInst, "SPAPI_GetInstrument");
		SPAPI_GetInstrumentByCode = (p_SPAPI_GetInstrumentByCode)GetProcAddress(hInst, "SPAPI_GetInstrumentByCode");
		SPAPI_SetLanguageId = (p_SPAPI_SetLanguageId)GetProcAddress(hInst, "SPAPI_SetLanguageId");
		SPAPI_Uninitialize = (p_SPAPI_Uninitialize)GetProcAddress(hInst, "SPAPI_Uninitialize");
		SPAPI_GetDllVersion = (p_SPAPI_GetDllVersion)GetProcAddress(hInst, "SPAPI_GetDllVersion");	
		SPAPI_GetAllTradesByArray = (p_SPAPI_GetAllTradesByArray)GetProcAddress(hInst, "SPAPI_GetAllTradesByArray");
		SPAPI_GetOrdersByArray = (p_SPAPI_GetOrdersByArray)GetProcAddress(hInst, "SPAPI_GetOrdersByArray");
		SPAPI_GetAllAccBalByArray  = (p_SPAPI_GetAllAccBalByArray)GetProcAddress(hInst, "SPAPI_GetAllAccBalByArray");
		SPAPI_GetInstrumentByArray = (p_SPAPI_GetInstrumentByArray)GetProcAddress(hInst, "SPAPI_GetInstrumentByArray");
		SPAPI_GetProductByArray = (p_SPAPI_GetProductByArray)GetProcAddress(hInst, "SPAPI_GetProductByArray");
		SPAPI_SendAccControl = (p_SPAPI_SendAccControl)GetProcAddress(hInst, "SPAPI_SendAccControl");

        //加载注册监听主动函数
        SPAPI_RegisterLoginReply = (p_SPAPI_RegisterLoginReply)GetProcAddress(hInst, "SPAPI_RegisterLoginReply");
        SPAPI_RegisterConnectingReply = (p_SPAPI_RegisterConnectingReply)GetProcAddress(hInst, "SPAPI_RegisterConnectingReply");
		SPAPI_RegisterAccountInfoPush = (p_SPAPI_RegisterAccountInfoPush)GetProcAddress(hInst, "SPAPI_RegisterAccountInfoPush");
		SPAPI_RegisterOrderReport = (p_SPAPI_RegisterOrderReport)GetProcAddress(hInst, "SPAPI_RegisterOrderReport");		
		SPAPI_RegisterOrderRequestFailed = (p_SPAPI_RegisterOrderRequestFailed)GetProcAddress(hInst, "SPAPI_RegisterOrderRequestFailed");		
		SPAPI_RegisterOrderBeforeSendReport = (p_SPAPI_RegisterOrderBeforeSendReport)GetProcAddress(hInst, "SPAPI_RegisterOrderBeforeSendReport");
		SPAPI_RegisterAccountLoginReply = (p_SPAPI_RegisterAccountLoginReply)GetProcAddress(hInst, "SPAPI_RegisterAccountLoginReply");		
		SPAPI_RegisterAccountLogoutReply = (p_SPAPI_RegisterAccountLogoutReply)GetProcAddress(hInst, "SPAPI_RegisterAccountLogoutReply");
		
		SPAPI_RegisterAccountPositionPush = (p_SPAPI_RegisterAccountPositionPush)GetProcAddress(hInst, "SPAPI_RegisterAccountPositionPush");
		SPAPI_RegisterUpdatedAccountPositionPush = (p_SPAPI_RegisterUpdatedAccountPositionPush)GetProcAddress(hInst, "SPAPI_RegisterUpdatedAccountPositionPush");
		SPAPI_RegisterUpdatedAccountBalancePush = (p_SPAPI_RegisterUpdatedAccountBalancePush)GetProcAddress(hInst, "SPAPI_RegisterUpdatedAccountBalancePush");
		SPAPI_RegisterTradeReport = (p_SPAPI_RegisterTradeReport)GetProcAddress(hInst, "SPAPI_RegisterTradeReport");
		SPAPI_RegisterLoadTradeReadyPush = (p_SPAPI_RegisterLoadTradeReadyPush)GetProcAddress(hInst, "SPAPI_RegisterLoadTradeReadyPush");
		SPAPI_RegisterApiPriceUpdate = (p_SPAPI_RegisterApiPriceUpdate)GetProcAddress(hInst, "SPAPI_RegisterApiPriceUpdate");
		SPAPI_RegisterTickerUpdate = (p_SPAPI_RegisterTickerUpdate)GetProcAddress(hInst, "SPAPI_RegisterTickerUpdate");
		
		SPAPI_RegisterProductListByCodeReply = (p_SPAPI_RegisterProductListByCodeReply)GetProcAddress(hInst, "SPAPI_RegisterProductListByCodeReply");
		SPAPI_RegisterInstrumentListReply = (p_SPAPI_RegisterInstrumentListReply)GetProcAddress(hInst, "SPAPI_RegisterInstrumentListReply");
		SPAPI_RegisterBusinessDateReply = (p_SPAPI_RegisterBusinessDateReply)GetProcAddress(hInst, "SPAPI_RegisterBusinessDateReply");
		SPAPI_RegisterMMOrderRequestFailed = (p_SPAPI_RegisterMMOrderRequestFailed)GetProcAddress(hInst, "SPAPI_RegisterMMOrderRequestFailed");
		SPAPI_RegisterMMOrderBeforeSendReport = (p_SPAPI_RegisterMMOrderBeforeSendReport)GetProcAddress(hInst, "SPAPI_RegisterMMOrderBeforeSendReport");
		SPAPI_RegisterQuoteRequestReceivedReport = (p_SPAPI_RegisterQuoteRequestReceivedReport)GetProcAddress(hInst, "SPAPI_RegisterQuoteRequestReceivedReport");
		SPAPI_RegisterAccountControlReply = (p_SPAPI_RegisterAccountControlReply)GetProcAddress(hInst, "SPAPI_RegisterAccountControlReply");
				
        //cout<<"load listen "<<endl;
        //注册回调监听
        SPAPI_RegisterLoginReply(ONLoginReplyAddr);
        SPAPI_RegisterConnectingReply(ONConnectedReplyAddr);
		SPAPI_RegisterAccountInfoPush(ONAccountInfoPushAddr);
		SPAPI_RegisterOrderReport(ONApiOrderReportAddr);
		SPAPI_RegisterOrderRequestFailed(ONApiOrderRequestFailedAddr);
		SPAPI_RegisterOrderBeforeSendReport(ONApiOrderBeforeSendReportAddr); 
		SPAPI_RegisterAccountLoginReply(ONAccountLoginReplyAddr);
		SPAPI_RegisterAccountLogoutReply(ONAccountLogoutReplyAddr);

		SPAPI_RegisterAccountPositionPush(ONAccountPositionPushAddr);
		SPAPI_RegisterUpdatedAccountPositionPush(ONUpdatedAccountPositionPushAddr);
		SPAPI_RegisterUpdatedAccountBalancePush(ONUpdatedAccountBalancePushAddr);
		SPAPI_RegisterTradeReport(ONApiTradeReportAddr);
		//SPAPI_RegisterLoadTradeReadyPush(ONApiLoadTradeReadyPushAddr);
		SPAPI_RegisterApiPriceUpdate(ONApiPriceUpdateAddr);
		SPAPI_RegisterTickerUpdate(ONApiTickerUpdateAddr);

		SPAPI_RegisterProductListByCodeReply(ONProductListByCodeReplyAddr);
		SPAPI_RegisterInstrumentListReply(ONInstrumentListReplyAddr);
		SPAPI_RegisterBusinessDateReply(ONBusinessDateReplyAddr);
		SPAPI_RegisterMMOrderRequestFailed(ONApiMMOrderRequestFailedAddr); 
		SPAPI_RegisterMMOrderBeforeSendReport(ONApiMMOrderBeforeSendReportAddr); 
		SPAPI_RegisterQuoteRequestReceivedReport(ONApiQuoteRequestReceivedAddr); 
		SPAPI_RegisterAccountControlReply(ONAccountControlReplyAddr);
		
        //cout<<"register listen "<<endl;


        
    }else
		{
			printf("\nCheck all dll file (libeay32.dll libssl32.dll msvcp100.dll msvcp120.dll msvcr100.dll msvcr120.dll spapidllm64.dll spapidllm64.lib ssleay32.dll) is loaded in:");
            cout<<"DIR: "<< chCurDir <<endl;
			Sleep(5000);
		}

    //执行初始化任务
    SPAPI_SetLanguageId(0);
    SPAPI_Initialize();


}


int SpApi::login(const dict &req)
{
	char host[256],user_id[256],password[256], license[256], app_id[16];
	int port;
	getString(req, "host", host);//
	getString(req, "userID", user_id);//
	getString(req, "password", password);//
	getString(req, "license", license);//
	getString(req, "app_id", app_id);//

	port = 8080;
    cout<<"app_id:"<< app_id <<endl;
	cout<<"host:"<< host <<endl;
	// getInt(req, "port", &port);

	SPAPI_SetLoginInfo(host,port,license,app_id,user_id,password);
	int i=SPAPI_Login();

	return i;
};

int SpApi::getAPIVersion()
{
	char ver_no[100], rel_no[100], suffix[100];
	int i=SPAPI_GetDllVersion(ver_no, rel_no, suffix);
	cout<<"SP API VER:"<< rel_no <<endl;
	return i;
};

int SpApi::loadInstrument()
{
	int rc;
	rc = SPAPI_LoadInstrumentList();
	return rc;

};

void SpApi::getInstrument()	
{
	
	int count = SPAPI_GetInstrumentCount();
	cout<<"getInstrumentCount:"<< count <<endl;

	SPApiInstrument *apiInstList;
	if (count <= 0) {printf("\n No Instrument \n"); return;}
	apiInstList = (SPApiInstrument *)malloc(count * sizeof(SPApiInstrument));
	SPAPI_GetInstrumentByArray(apiInstList);
	for (int i = 0; i < count; i++) {
		SPApiInstrument& instrument = apiInstList[i];
		int dec = (int)instrument.DecInPrice;

		dict data;

		data["ContractSize"]=instrument.ContractSize;
		data["MarketCode"]=instrument.MarketCode;
		data["InstCode"]=instrument.InstCode;
		data["InstName"]=instrument.InstName;
		data["Ccy"]=instrument.Ccy;
		data["DecInPrice"]=dec;
		data["InstType"]=instrument.InstType;

		api->onInstrument(data);
	}
	free(apiInstList);


};

void SpApi::loadProductInfoListByMarket(string code)
{
	int rc;
	char* prodCode=(char*)code.c_str();
	rc = SPAPI_LoadProductInfoListByMarket(prodCode);
	printf("\nLoad Market Report Reply:%d ",rc);
	api->getProduct();

};


void SpApi::loadProductInfoListByCode(string code)
{
	int rc;
	char* prodCode=(char*)code.c_str();
	cout<<"Load Code:"<< prodCode <<endl;
	rc = SPAPI_LoadProductInfoListByCode(strupr(prodCode));

};

void SpApi::getProductByCode(string code)	
{
	int rc;
	char* prodCode=(char*)code.c_str();
	SPApiProduct prod;
	rc = SPAPI_GetProductByCode(prodCode, &prod);
	cout<<"out:"<< rc <<endl;
	if (rc == 0)
		printf("\n ProdCode=%s , ProdName=%s , InstCode=%s ", prod.ProdCode, prod.ProdName, prod.InstCode);  
};		

void SpApi::getProduct()		
{

    int count = SPAPI_GetProductCount();
	cout<<"Code Num:"<< count <<endl;
	SPApiProduct *apiProdList2;
	if (count <= 0) {printf("\n No Product \n"); return;}
	apiProdList2 = (SPApiProduct *)malloc(count * sizeof(SPApiProduct));
	SPAPI_GetProductByArray(apiProdList2);
	for (int i = 0; i < count; i++) {
		SPApiProduct& prod = apiProdList2[i];
		dict data;

		data["ProdType"]=prod.ProdType;
		data["ProdCode"]=prod.ProdCode;
		data["ProdName"]=prod.ProdName;
		data["InstCode"]=prod.InstCode;
		data["ExpiryDate"]=prod.ExpiryDate;
		data["LotSize"]=prod.LotSize;
		data["TickSize"]=prod.TickSize;
		
		data["Underlying"]=prod.Underlying;
		data["CallPut"]=prod.CallPut;
		data["Strike"]=prod.Strike;

		api->onProduct(data);
	
	}
	free(apiProdList2);

};


void SpApi::subscribeQuote(const dict &req)
{
	int tc;
	char prodcode[16], userId[16] ;

	getString(req, "userId", userId);//
	getString(req, "prodcode", prodcode);//
	cout<<"prodcode:"<< prodcode <<endl;

	tc=1;

	int rc = SPAPI_SubscribeQuoteRequest(userId,prodcode,tc);

	int rc1 = SPAPI_SubscribePrice(userId, prodcode, tc);
	printf("\n Subscribe:%d %d %s",rc,rc1,prodcode);
};

void SpApi::getAllAccBal(const dict &req)
{

	vector<SPApiAccBal> apiAccBalList;
	char user[16];

	getString(req, "userId", user);//
	SPAPI_GetAllAccBal(user, apiAccBalList);
	for (int i = 0; i < apiAccBalList.size(); i++) {
		SPApiAccBal& accBal = apiAccBalList[i];
		// this->OnUpdatedAccountBalancePush(const SPApiAccBal *accBal);
		printf("\n[No: %d, Acc No:%s]  Ccy=%s , CashBf=%f , NotYetValue=%f , TodayCash=%f , TodayOut=%f,  Unpresented=%f ",i+1, user, accBal.Ccy, accBal.CashBf, accBal.NotYetValue, accBal.TodayCash, accBal.TodayOut, accBal.Unpresented);
	}	
};

void SpApi::getAccInfo(const dict &req)
{
	SPApiAccInfo acc_info;
	int rc;
	char user[16];

	getString(req, "userId", user);//
	memset(&acc_info, 0, sizeof(SPApiAccInfo));
	rc = SPAPI_GetAccInfo(user, &acc_info);
	if (rc == 0)
	{	
		dict data;

		data["NAV"]=acc_info.NAV;
		data["BuyingPower"]=acc_info.BuyingPower;
		// data["CashBal"]=acc_info.CashBal;
		// data["MarginCall"]=acc_info.MarginCall;
		data["CommodityPL"]=acc_info.CommodityPL;
		// data["LockupAmt"]=acc_info.LockupAmt;
		// data["CreditLimit"]=acc_info.CreditLimit;
		// data["MaxMargin"]=acc_info.MaxMargin;
		// data["MaxLoanLimit"]=acc_info.MaxLoanLimit;
		// data["TradingLimit"]=acc_info.TradingLimit;
		data["RawMargin"]=acc_info.RawMargin;
		data["IMargin"]=acc_info.IMargin;
		// data["MMargin"]=acc_info.MMargin;
		// data["TodayTrans"]=acc_info.TodayTrans;
		// data["LoanLimit"]=acc_info.LoanLimit;
		// data["TotalFee"]=acc_info.TotalFee;
		// data["LoanToMR"]=acc_info.LoanToMR;
		// data["LoanToMV"]=acc_info.LoanToMV;
		// data["AccName"]=acc_info.AccName;
		data["BaseCcy"]=acc_info.BaseCcy;
		// data["MarginClass"]=acc_info.MarginClass;

		// data["TradeClass"]=acc_info.TradeClass;
		data["ClientId"]=acc_info.ClientId;
		// data["AEId"]=acc_info.AEId;
		// data["AccType"]=acc_info.AccType;
		// data["CtrlLevel"]=acc_info.CtrlLevel;
		// data["Active"]=acc_info.Active;
		// data["MarginPeriod"]=acc_info.MarginPeriod;
		// cout<<"app_id:"<< app_id <<endl;	

		api->onAccountInfoPush(data);

	}

};

void SpApi::getAllPos(const dict &req)
{
	int i;
	char user[16];
	vector<SPApiPos> apiPosList;

	getString(req, "userId", user);//GetUserId(user);

	SPAPI_GetAllPos(user, apiPosList);
	for (i = 0; i < apiPosList.size(); i++) {
		SPApiPos& task_data = apiPosList[i];

		dict data;
		data["Qty"]=task_data.Qty;
		data["DepQty"]=task_data.DepQty;
		data["LongQty"]=task_data.LongQty;
		data["ShortQty"]=task_data.ShortQty;
		data["TotalAmt"]=task_data.TotalAmt;
		data["DepTotalAmt"]=task_data.DepTotalAmt;
		data["LongTotalAmt"]=task_data.LongTotalAmt;
		data["ShortTotalAmt"]=task_data.ShortTotalAmt;
		data["PLBaseCcy"]=task_data.PLBaseCcy;
		data["PL"]=task_data.PL;
		data["ExchangeRate"]=task_data.ExchangeRate;
		data["AccNo"]=task_data.AccNo;
		data["ProdCode"]=task_data.ProdCode;
		data["LongShort"]=task_data.LongShort;
		data["DecInPrice"]=task_data.DecInPrice;
		
		this->onAccountPositionPush(data);

		// printf("\nAll Pos>> ProdCode=%s,Prev.=%d @ %f,DayLong=%d @ %f,DayShort=%d @ %f, Rate:%f", pos.ProdCode, (pos.LongShort == 'B')?pos.Qty:-1*pos.Qty, pos.TotalAmt, pos.LongQty, pos.LongTotalAmt, pos.ShortQty, pos.ShortTotalAmt, pos.ExchangeRate);
	}
	// if (i == 0)printf("No Pos");

};

int SpApi::reqOrderInsert(const dict &req)
{
	SPApiOrder myreq = SPApiOrder();
	memset(&myreq, 0, sizeof(myreq));
	getString(req, "UserId", myreq.Initiator);
	getString(req, "UserId", myreq.AccNo);
	getString(req, "ProdCode", myreq.ProdCode);
	getString(req, "ClOrderId", myreq.ClOrderId);
	getDouble(req, "Price", &myreq.Price);
	getInt(req, "Qty", &myreq.Qty);
	getChar(req, "BuySell", &myreq.BuySell);
	getChar(req, "DecInPrice", &myreq.DecInPrice);
	getInt(req, "IntOrderNo", &myreq.IntOrderNo);
	if(myreq.IntOrderNo > 0) 
		myreq.OrderOptions = 1;
	else myreq.OrderOptions = 0;

	// myreq.OrderOptions = 0;
	myreq.ValidType=0;
	myreq.OrderType=ORD_LIMIT;
	myreq.CondType=0;
	myreq.OpenClose=1;

	
	return SPAPI_AddOrder(&myreq);
};

void SpApi::reqOrderDelete(const dict &req)
{
	char prodcode[16], clOrderId[40];
	long int_order_no;
	int rc;
	char userId[16], accNo[16];

	getString(req, "userId", userId);
	getString(req, "accNo", accNo);
	getString(req, "ProdCode", prodcode);
	getString(req, "ClOrderId", clOrderId);
	getLong(req, "orderID", &int_order_no);

	// printf("\n Delete code:%s clid:%s no:%d useid:%s accNo:%s\n",prodcode,clOrderId,int_order_no,userId,accNo);


	rc = SPAPI_DeleteOrderBy(userId, accNo, int_order_no, prodcode, clOrderId);
	if (rc != 0)printf("\n DeleteOrderBy, return : %d \n", rc);

};


///-------------------------------------------------------------------------------------
///Python封装
///-------------------------------------------------------------------------------------

class PySpApi : public SpApi
{
public:
	using SpApi::SpApi;

	void onLoginReply(long code) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, SpApi, onLoginReply,code);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};

    void onConnectedReply(long id,long code) override
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onConnectedReply,id,code);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiOrderRequestFailed(const dict &data, int code, char error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiOrderRequestFailed,data,code,error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiOrderReport(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiOrderReport,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiOrderBeforeSendReport(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiOrderBeforeSendReport,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAccountLoginReply(int code, char error)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onAccountLoginReply,code,error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAccountLogoutReply(int code, char error)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onAccountLogoutReply,code,error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAccountInfoPush(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onAccountInfoPush,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onAccountPositionPush(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onAccountPositionPush,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUpdatedAccountPositionPush(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onUpdatedAccountPositionPush,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUpdatedAccountBalancePush(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onUpdatedAccountBalancePush,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiTradeReport(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiTradeReport,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiPriceUpdate(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiPriceUpdate,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onApiTickerUpdate(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiTickerUpdate,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onInstrument(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onInstrument,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onProduct(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onProduct,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};


	void onApiMMOrderRequestFailed(const dict &data, int code, char error)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiMMOrderRequestFailed,data,code,error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
	void onApiLoadTradeReadyPush(const dict &data)
	{
		try
		{
			PYBIND11_OVERLOAD(void,SpApi,onApiLoadTradeReadyPush,data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnsp, m)
{
    class_<SpApi, PySpApi> SpApi(m, "SpApi", module_local());
    SpApi
        .def(init<>())
        .def("createApi", &SpApi::createApi)
        .def("getAPIVersion", &SpApi::getAPIVersion)
        .def("login", &SpApi::login)
    	.def("loadInstrument", &SpApi::loadInstrument)
        .def("getProduct", &SpApi::getProduct)
        .def("getInstrument", &SpApi::getInstrument)
        .def("loadProductInfoListByMarket", &SpApi::loadProductInfoListByMarket)
        .def("loadProductInfoListByCode", &SpApi::loadProductInfoListByCode)
        .def("getProductByCode", &SpApi::getProductByCode)
        .def("subscribeQuote", &SpApi::subscribeQuote)
        .def("getAllAccBal", &SpApi::getAllAccBal)
        .def("getAccInfo", &SpApi::getAccInfo)
        .def("getAllPos", &SpApi::getAllPos)
        .def("reqOrderInsert", &SpApi::reqOrderInsert)
        .def("reqOrderDelete", &SpApi::reqOrderDelete)


        .def("onLoginReply", &SpApi::onLoginReply)
        .def("onConnectedReply", &SpApi::onConnectedReply)
        .def("onApiOrderRequestFailed", &SpApi::onApiOrderRequestFailed)
        .def("onApiOrderReport", &SpApi::onApiOrderReport)
        .def("onApiOrderBeforeSendReport", &SpApi::onApiOrderBeforeSendReport)
        .def("onAccountLoginReply", &SpApi::onAccountLoginReply)
        .def("onAccountLogoutReply", &SpApi::onAccountLogoutReply)
        .def("onAccountInfoPush", &SpApi::onAccountInfoPush)
        .def("onAccountPositionPush", &SpApi::onAccountPositionPush)
        .def("onUpdatedAccountPositionPush", &SpApi::onUpdatedAccountPositionPush)
        .def("onUpdatedAccountBalancePush", &SpApi::onUpdatedAccountBalancePush)
        .def("onApiTradeReport", &SpApi::onApiTradeReport)
        .def("onApiPriceUpdate", &SpApi::onApiPriceUpdate)
        .def("onApiTickerUpdate", &SpApi::onApiTickerUpdate)

        .def("onApiMMOrderRequestFailed", &SpApi::onApiMMOrderRequestFailed)
        .def("onApiLoadTradeReadyPush", &SpApi::onApiLoadTradeReadyPush)
        .def("onInstrument", &SpApi::onInstrument)
        .def("onProduct", &SpApi::onProduct)
        ;
};
