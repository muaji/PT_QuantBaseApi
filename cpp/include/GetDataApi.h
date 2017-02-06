#ifndef GETDATAAPI_H
#define GETDATAAPI_H

#ifdef WIN32
#ifndef API_EXPORT  
#define API_EXPORT _declspec(dllexport)  
#else  
#define API_EXPORT _declspec(dllimport)  
#endif
#endif

namespace PT_QuantPlatform{
	class TradeDataApi;
	class GetDataSpi{
	public:
		virtual void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum){};		//�����,��¼�ɹ��󼴻����ϵ��øûص�
		//ʵʱ����
		virtual void OnRecvMarket(TDF_MARKET_DATA* pMarket){};									//����
		virtual void OnRecvFuture(TDF_FUTURE_DATA* pFuture){};									//�ڻ�
		virtual void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture){};							//��Ȩ
		virtual void OnRecvIndex(TDF_INDEX_DATA* pIndex){};										//ָ��
		virtual void OnRecvTransaction(TDF_TRANSACTION* pTransaction){};						//���
		virtual void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue){};							//ί�ж���
		virtual void OnRecvOrder(TDF_ORDER* pOrder){};											//���ί�����ݣ��������У�
		virtual void OnRecvGDKLine(GD_Kline_Data* pKline){};									//K������

		//ÿ���������ڱ������֪ͨ�������ӿڣ���������ʷ����ʵʱ
		virtual void OnRecvRspSimulationTimelineConfirmed(GD_SimulationTimelineConfirmed_Rsp* pConfirmed){}; //ģ��ʱ����ȷ�ϻص�
		virtual void OnRecvDayBegin(GD_ISODateTimeType pDate){};						//���յ�ǰ������		
		virtual void OnRecvDayEnd(GD_ISODateTimeType pDate){};							//���յ�������Ϣ
		virtual void OnRecvRspOver(){};													//ÿ����ʷ����������������������ӿ�

		//ָ������
		virtual void OnRspTradingDay(GD_ISODateTimeType* pDay, int dayNum){};
		//ϵͳ��Ϣ
		virtual void OnConnect(PT_ServerTypeCD serverType){};
		virtual void OnDisconnect(PT_ServerTypeCD serverType){};
		virtual void OnReconnectStatus(PT_ServerTypeCD serverType, const bool successed){};

		virtual void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData){};		//����ʱЧ��״̬�л�֪ͨ��ͨ�����
		virtual void OnError(string error){};	//������Ϣ
		GetDataSpi(){};
		~GetDataSpi(){};
	};
#ifdef WIN32
	class API_EXPORT GetDataApi{
#else
	class GetDataApi{
#endif
	public:
		bool Login(char* user, char* pass, int &err);
		//����ʵʱ����
		//tick���ݺ�k�߿���ͬʱ����ReqUpdateSubStockCode����ͬʱ�޸�k�ߺ�tick�Ķ��Ĵ���
		void ReqRealtimeData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);				//����ʵʱtick, isAllMarket = true �������д���, isFromOpening = true ��ȫ��������ǰʱ�̵����ݣ�subDataType Ϊö��ֵѡ��������������������
		void ReqRealtimeGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);				//����ʵʱk�� type Ϊk���������ͣ�һ��ֻ�ܶ���һ�����ڣ���������ͬ�ϡ����ݻص�Ϊ OnRecvGDKLine
		void ReqUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);			//���¶��Ĵ��룬�������ӡ��滻��ɾ�����ĵĴ��� 
		//����ģ������ʱ����
		void ReqSimulationTimeline(GD_ISODateTimeType beginTime, GD_PlaybackSpeedType speadTyp, int &err);
		void ReqSimulationTickData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
		void ReqSimulationGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
		void ReqSimulationUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
		//������ʷ����
		//������ʷLevel2 tick����
		void ReqHistoryData(GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, GD_PlaybackSpeedType modelType, std::vector<char*> &subCodes, bool isAllMarket, int &err);	//������ʷlevel2 tick���� GD_SimuModelTypeΪ���ݻط��ٶ�ѡ��, fastΪ����٣�normalΪ����ʵ����ͬ�����ٶ�
		void ReqHistoryGDKLineData(GD_CycType type, GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, std::vector<char*> &subCodes, bool isAllMarket, int &err);						//������ʷK����������	�����ݻص�Ϊ OnRecvGDKLine
		void ReqTradingDay(GD_ISODateTimeType beginDay, GD_ISODateTimeType endDay, int &err);		//��ѯ�Ľ������б�
		//ָ��ӿ�
		void calculateKLineByTick(std::vector<GD_CycType> cycs);
		std::vector<GD_StockBaseInfo> getStockBaseInfo(GD_CodeType code, GD_ListStatusType listType, GD_EquTypeCD equType, int &err);
		std::vector<GD_RestorationFactor> getRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);			//ǰ��Ȩ����
		std::vector<GD_RestorationFactor> getAFRestorationFactor(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);			//��Ȩ����
		std::vector<GD_DetailMarketDayKline> getDetailMarketDayKline(GD_CodeType code, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
		std::vector<GD_StockFactors> getStockFactors(GD_CodeType code, vector<char*> &factorKeys, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);

	};
};


extern "C"
{
#ifdef WIN32
	API_EXPORT const char* GetQuantPlatformApiVersion();
	API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, bool enableLog = true);
	API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApiEnableSimulationTrade(PT_QuantPlatform::TradeDataApi* tApi, PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, int &err, bool autoReq = false, bool enableLog = true);
	API_EXPORT void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
#else
	const char* GetQuantPlatformApiVersion();
	PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, bool enableLog = true);
	PT_QuantPlatform::GetDataApi* CreateGetDataApiEnableSimulationTrade(PT_QuantPlatform::TradeDataApi* tApi, PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, int &err, bool autoReq = false, bool enableLog = true);
	void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
#endif
}

#endif // GETDATAAPI_H