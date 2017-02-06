#ifndef TRADEDATAAPI_H
#define TRADEDATAAPI_H

#ifdef WIN32
#ifndef API_EXPORT  
	#define API_EXPORT _declspec(dllexport)
#endif
#endif

namespace PT_QuantPlatform{
	class TradeDataSpi
	{
	public: //ϵͳ�ص�
		virtual void OnRspUserTradeInfo(const TD_UserTradeInfoRsp *rsp) = 0;		//�û���¼�ص�
		virtual void OnTDConnect(PT_ServerTypeCD serverType) = 0;									//���ӳɹ�
		virtual void OnTDDisConnect(PT_ServerTypeCD serverType) = 0;								//�Ͽ�
		virtual void OnTDReconnectStatus(PT_ServerTypeCD serverType, const bool successed) = 0;		//������������״̬
	
	public: //ҵ���߼��ص�

		virtual void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, int error) = 0;				//���붩���ص�
		virtual void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, int error) = 0;				//�޸Ķ����ص�
		virtual void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, int error) = 0;				//ɾ�������ص�

		virtual void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, int error, bool isEnd) = 0;					//��ѯ�����ص�
		virtual void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, int error, bool isEnd) = 0;					//��ѯ�ɽ��ص�
		virtual void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, int error, bool isEnd) = 0;			//��ѯ�ֲֻص�

		virtual void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, int error, bool isEnd) = 0;                           // ��ѯ�ʽ��ʺŻص�
		virtual void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, int error, bool isEnd) = 0;                                // ��ѯ��ȯ��ծ�ص�
		virtual void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp, int error) = 0;								// ��ѯ����ί�����ص�
		virtual void OnRspQrySecuritiesLendingAmount(const TD_QrySecuritiesLendingAmount_Rsp* rsp, int error, bool isEnd) = 0;	// ��ѯ����ȯ�б�ص�

		virtual void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice) = 0;    	//����״̬�仯֪ͨ
		virtual void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice) = 0;						//�ɽ�״̬����֪ͨ

	public:
		TradeDataSpi(){};
		~TradeDataSpi(){};
	};
#ifdef WIN32
	class API_EXPORT TradeDataApi{
#else
	class TradeDataApi{
#endif
	public:
		bool Login(char* user, char* pass, int &err);
		void SetNewBackTest(double stampTax, double transferFees, double commissions, char* szComment, int &err);

		virtual void OrderInsert(TD_OrderInsert_Req* req);				//���붩��
		virtual void OrderModify(TD_OrderModify_Req* req);				//�޸Ķ���
		virtual void OrderDelete(TD_OrderDelete_Req* req);				//ɾ������

		virtual void QryOrder(TD_QryOrder_Req* req);											//��ѯ�������ж���
		virtual void QryMatch(TD_QryMatch_Req* req);											//��ѯ���гɽ�
		virtual void QryPosition(TD_QryPosition_Req* req);										//��ѯͷ��

		virtual void QryCapitalAccount(TD_QryCapital_Req* req);									// ��ѯ�ʽ��ʺ�
		virtual void QrySecuDebt(TD_QrySecuDebt_Req* req);										// ��ѯ��ȯ��ծ
		virtual void QryMaxEntrustCount(TD_QryMaxEntrustCount_Req* req);						// ��ѯ����ί����
		virtual void QrySecuritiesLendingAmount(TD_QrySecuritiesLendingAmount_Req* req);		// ��ѯ����ȯ�б�
	};
};

extern "C"
{
#ifdef WIN32
	API_EXPORT PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	API_EXPORT PT_QuantPlatform::TradeDataApi* CreateSimulationTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	API_EXPORT void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
#else
	PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	PT_QuantPlatform::TradeDataApi* CreateSimulationTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool enableLog = true);
	void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
#endif
}

#endif // TRADEDATAAPI_H