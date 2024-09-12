# include "vnsp.h"

///-------------------------------------------------------------------------------------
///C++的回调函数
///-------------------------------------------------------------------------------------

void SPDLLCALL LoginReplyAddr(char* user_id, long ret_code, char* ret_msg)
{
	api->loginReplyAddr(user_id, ret_code, ret_msg);
};


///-------------------------------------------------------------------------------------
///C++的主动函数
///-------------------------------------------------------------------------------------

int SpApi::initialize()
{
    HINSTANCE hInst = LoadLibraryA("spapidllm64.dll");

    if (hInst != NULL)
    {
        //加载注册监听主动函数
        SPAPI_RegisterLoginReply = (p_SPAPI_RegisterLoginReply)GetProcAddress(hInst, "SPAPI_RegisterLoginReply");

        //加载功能调用主动函数
        SPAPI_Initialize = (p_SPAPI_Initialize)GetProcAddress(hInst, "SPAPI_Initialize");
        SPAPI_SetLoginInfo = (p_SPAPI_SetLoginInfo)GetProcAddress(hInst, "SPAPI_SetLoginInfo");
        SPAPI_Login = (p_SPAPI_Login)GetProcAddress(hInst, "SPAPI_Login");

        //注册回调监听
        SPAPI_RegisterLoginReply(LoginReplyAddr);
    }

    //执行初始化任务
	return SPAPI_Initialize();
}


void SpApi::setLoginInfo(string host, int port, string license, string app_id, string user_id, string password)
{
    return SPAPI_SetLoginInfo((char*)host.c_str(), port, (char*)license.c_str(), (char*)user_id.c_str(), (char*)app_id.c_str(), (char*)password.c_str());
}


int SpApi::login()
{
    return SPAPI_Login();
}


///-------------------------------------------------------------------------------------
///Python封装
///-------------------------------------------------------------------------------------

class PySpApi : public SpApi
{
public:
	using SpApi::SpApi;

	void loginReplyAddr(string user_id, long ret_code, string ret_msg) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, SpApi, loginReplyAddr, user_id, ret_code, ret_msg);
		}
		catch (const error_already_set& e)
		{
			cout << e.what() << endl;
		}
	};
};


PYBIND11_MODULE(vnctptd, m)
{
    class_<SpApi, PySpApi> SpApi(m, "SpApi", module_local());
    SpApi
        .def(init<>())
        .def("initialize", &SpApi::initialize)
        .def("setLoginInfo", &SpApi::setLoginInfo)
        .def("login", &SpApi::login)

        .def("loginReplyAddr", &SpApi::loginReplyAddr)
        ;
};
