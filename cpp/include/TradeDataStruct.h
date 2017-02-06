#ifndef TRADEDATASTRUCT_H
#define TRADEDATASTRUCT_H

//#include "GetDataStruct.h"
/* ��һ���ֽڲ���*/
#pragma pack(push)
#pragma pack(1)

#ifndef GETDATASTRUCT_H
typedef char GD_CodeType[32];
typedef char GD_CodeName[32];
typedef char GD_ISODateTimeType[21];	//���ں�ʱ������(��ʽ yyyy-MM-dd hh:mm:ss)
#endif

typedef char TD_OrderIdType[32];
typedef char TD_AccountType[32];
typedef char TD_Text[128];

enum TD_BrokerType			//ȯ������
{
	TD_BrokerType_None,
	TD_BrokerType_dongwu,
	TD_BrokerType_guangda,
	TD_BrokerType_guotai,
	TD_BrokerType_guoxin,
	TD_BrokerType_haitong,
	TD_BrokerType_shenwan,
	TD_BrokerType_yinhe,
	TD_BrokerType_zhaoshang,
	TD_BrokerType_fangzheng,
	TD_BrokerType_AC,
	TD_BrokerType_zhongxin,
	TD_BrokerType_anxin,
	TD_BrokerType_dongbei,
	TD_BrokerType_huataiwang,
	TD_BrokerType_hengtai,
	TD_BrokerType_zhongjing,
	TD_BrokerType_guangfa,
	TD_BrokerType_huabao,
	TD_BrokerType_xuntou,
	TD_BrokerType_xibu,
	TD_BrokerType_IMSWT,
	TD_BrokerType_huatai
};

enum TD_OrderType
{
	TD_OrderType_Limit,		//�޼۵�
	TD_OrderType_Market		//�м۵�
};

enum TD_TradeType
{
	// ������
	TD_TradeType_Sell					= -200,		//��ͨ����
	TD_TradeType_SellBySecuLending,					//��ȯ����
	TD_TradeType_SellSecurityRtnCash,				//��ȯ����

	TD_TradeType_None					= 0,
	TD_TradeType_RtnSecurity			= 1,		//ֱ�ӻ�ȯ
	TD_TradeType_RtnCash,							//ֱ�ӻ���

	// ����
	TD_TradeType_Buy					= 100,		//��ͨ����
	TD_TradeType_BuyOnMargin,						//��������
	TD_TradeType_BuySecurityRtnSecu,				//��ȯ��ȯ
};

enum TD_OffsetType
{
	TD_OffsetType_None,
	TD_OffsetType_Open,					//����
	TD_OffsetType_Close,				//ƽ��
};

enum TD_OrderStatusType
{
	TD_OrderStatusType_fail			= -10,	//ָ��ʧ��
	TD_OrderStatusType_partRemoved,			//���ֳ���
	TD_OrderStatusType_removed,				//�����ɹ�
	TD_OrderStatusType_allDealed,			//ȫ���ɽ�

	TD_OrderStatusType_unAccpet		= 0,	//δ����
	TD_OrderStatusType_accpeted,			//�ѽ���δ����
	TD_OrderStatusType_queued,				//�����Ŷ�	(������״̬)
	TD_OrderStatusType_toModify,			//�����ĵ�
	TD_OrderStatusType_modifing,			//�ѱ��ĵ�
	TD_OrderStatusType_modified,			//�ĵ�����
	TD_OrderStatusType_toRemove,			//��������
	TD_OrderStatusType_removing,			//�ѱ�����
	TD_OrderStatusType_partDealed,			//���ֳɽ�
};

/// �����г�
enum TD_MarketType
{
	TD_MarketType_NULL,		//δָ��
	TD_MarketType_SZ_A,		//����A
	TD_MarketType_SZ_B,		//����B
	TD_MarketType_SH_A,		//�Ϻ�A
	TD_MarketType_SH_B,		//�Ϻ�B
	TD_MarketType_XSB		//������
};

//�������������ʹ���
typedef char PT_ServerTypeCD;
const PT_ServerTypeCD		Production_PT_ServerTypeCD = 20;		//�����������׷�����
const PT_ServerTypeCD		Test_PT_ServerTypeCD = 22;				//���Ի������׷�����

// ����
struct TD_Base_Msg
{
	int		nReqId;						//����ID���пͻ���APIά����ΨһID��

	int		nUserInt;					//�û������ֶ�
	double	nUserDouble;
	TD_Text szUseStr;

	int		nUserId;					//�ͻ��˱��
	int		nAccountId;					//ȯ���ʽ��˻�Id

	TD_Base_Msg()
	{
		nReqId = 0;

		nUserInt = 0;
		nUserDouble = 0;
		memset(szUseStr, 0, sizeof(TD_Text));

		nUserId = 0;
		nAccountId = 0;
	}
	virtual ~TD_Base_Msg()
	{

	}
};

// �µ�
struct TD_OrderInsert_Req : TD_Base_Msg
{
	__int64         nOrderId;							//������ά��������Ψһ��
	TD_OrderIdType	szOrderStreamId;		//ί�б�ţ�broker ��������Ψһ��ţ�

	GD_CodeType		szContractCode;			//֤ȯ��Լ����
	GD_CodeName		szContractName;			//֤ȯ��Լ����
	TD_OrderType	nOrderType;				//�м��޼۵�
	TD_TradeType	nTradeType;				//�������� ��������ȯ��
	TD_OffsetType	nOffsetType;			//��ƽ������

	double			nOrderPrice;			//�걨��
	int				nOrderVol;				//�걨��

	GD_ISODateTimeType szInsertTime;		//����ί��ʱ��

	TD_OrderInsert_Req()
	{
		nOrderId = 0;
		memset(szOrderStreamId, 0, sizeof(TD_OrderIdType));

		memset(szContractCode, 0, sizeof(GD_CodeType));
		memset(szContractName, 0, sizeof(GD_CodeName));
		nTradeType = TD_TradeType_None;
		nOrderType = TD_OrderType_Limit;
		nOffsetType = TD_OffsetType_None;

		nOrderPrice = 0;
		nOrderVol= 0;

		memset(szInsertTime, 0, sizeof(GD_ISODateTimeType));
	}
	virtual ~TD_OrderInsert_Req()
	{

	}
};

//�޸Ķ�������
struct TD_OrderModify_Req : TD_Base_Msg		
{
	__int64			nOrderId;				//����Id
	double			nPrice;					//�޸��걨��
	int				nVol;					//�޸��걨��

	TD_OrderModify_Req()
	{
		nOrderId = 0;
		nPrice = 0;
		nVol = 0;
	}
	virtual ~TD_OrderModify_Req()
	{

	}
};

// ����
struct TD_OrderDelete_Req : TD_Base_Msg
{
	__int64 nOrderId;
	TD_OrderDelete_Req()
	{
		nOrderId = 0;
	}
	virtual ~TD_OrderDelete_Req()
	{

	}
};

//ί�в�ѯ����
struct TD_QryOrder_Req : TD_Base_Msg
{
	__int64					nOrderId;				//ί�б��
	GD_CodeType			szContractCode;			//֤ȯ��Լ����
	TD_QryOrder_Req()
	{
		nOrderId = 0;

		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryOrder_Req()
	{

	}
};

//�ɽ���ѯ����
struct TD_QryMatch_Req : TD_Base_Msg
{
	GD_CodeType		szContractCode;			    //֤ȯ��Լ����
	TD_QryMatch_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryMatch_Req()
	{

	}
};

//�ֲֲ�ѯ����
struct TD_QryPosition_Req : TD_Base_Msg
{
	GD_CodeType		szContractCode;			    //֤ȯ��Լ����
	TD_QryPosition_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QryPosition_Req()
	{

	}
};

//����ί������ѯ����
struct TD_QryMaxEntrustCount_Req : TD_Base_Msg
{
	GD_CodeType szContractCode;       // ��Ʊ����
	double      nPrice;		          // �۸�
	TD_TradeType nTraderType;         // ������Ϊ
	TD_QryMaxEntrustCount_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		nPrice = 0;
		nTraderType = TD_TradeType_None;
	}
	virtual ~TD_QryMaxEntrustCount_Req()
	{

	}
};

//����ȯ��ѯ����
struct TD_QrySecuritiesLendingAmount_Req : TD_Base_Msg  
{
	GD_CodeType szContractCode;       // ��Ʊ����
	TD_QrySecuritiesLendingAmount_Req()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
	}
	virtual ~TD_QrySecuritiesLendingAmount_Req()
	{

	}
};

typedef TD_Base_Msg TD_QryCapital_Req;				//�ʽ��ѯ����
typedef TD_Base_Msg TD_QrySecuDebt_Req;				//��ȯ��ծ��ѯ����
typedef TD_Base_Msg TD_Base_Req;						//�����޲�������

//����״̬�仯֪ͨ
struct TD_OrderStatusChangeNotice : TD_OrderInsert_Req
{
	TD_OrderStatusType	nStatus;				//״̬
	double				nDealedPrice;			//�ɽ�����
	int					nDealedVol;				//�ɽ�����

	TD_Text             szText;

	TD_OrderStatusChangeNotice()
	{
		nStatus = TD_OrderStatusType_unAccpet;
		nDealedPrice = 0;
		nDealedVol = 0;

		memset(szText, 0, sizeof(szText));
	}
	virtual ~TD_OrderStatusChangeNotice()
	{

	}
};

//�ɽ��ص�֪ͨ
struct TD_OrderMatchNotice : TD_Base_Msg
{
	__int64     		nOrderId;				//����ί�б��
	__int64  			nMatchStreamId;			//�ɽ�ϵͳ���
	double				nMatchPrice;			//�ɽ���
	int					nMatchVol;				//�ɽ���

	GD_CodeType szContractCode;				    // ��Ʊ����
	GD_ISODateTimeType  szMatchTime;			//�ɽ�ʱ��

	TD_OrderMatchNotice()
	{
		nOrderId = 0;
		nMatchStreamId = 0;
		nMatchPrice = 0;
		nMatchVol = 0;

		memset(szContractCode, 0, sizeof(GD_CodeType));
		memset(szMatchTime, 0, sizeof(GD_ISODateTimeType));
	}
	virtual ~TD_OrderMatchNotice()
	{

	}
};

typedef TD_OrderStatusChangeNotice TD_OrderInsert_Rsp;	//���붩����Ӧ	
typedef TD_OrderDelete_Req		 TD_OrderDelete_Rsp;	//����������Ӧ
typedef TD_OrderModify_Req		 TD_OrderModify_Rsp;	//�޸Ķ�����Ӧ

//������ѯ��Ӧ
typedef TD_OrderStatusChangeNotice TD_QryOrder_Rsp;
//�ɽ���ѯ��Ӧ
typedef TD_OrderMatchNotice TD_QryMatch_Rsp;

//�ֲֲ�ѯ�ص�
struct TD_QryPosition_Rsp : TD_Base_Msg
{
	GD_CodeType		szContractCode;			//֤ȯ��Լ����

	int     nPosition;                       //  �ֲ�����
	double      nPrice;                      //  �ֲ־���

	double  nProfit;                         //  ��ӯ
	TD_QryPosition_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		nPosition = 0;
		nPrice = 0;
		nProfit = 0;
	}
	virtual ~TD_QryPosition_Rsp()
	{

	}
};

//  ��ѯ�ʽ��ʺŻص�
struct TD_QryCapital_Rsp : TD_Base_Msg
{
	double m_fundbal;                     //  �ʽ�ծ�ܶ�
	double m_fundavl;	                  //  �ʽ���ý��  
	TD_QryCapital_Rsp()
	{
		m_fundbal = 0;
		m_fundavl = 0;
	}
	virtual ~TD_QryCapital_Rsp()
	{

	}
};

//  ��ѯ��ȯ��ծ�ص�
struct TD_QrySecuDebt_Rsp : TD_Base_Msg
{
	GD_CodeType szContractCode;       // ��Ʊ����
	int  m_dstkbal;                   // ��ծ�ܹ��� 
	TD_QrySecuDebt_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		m_dstkbal = 0;
	}
	virtual ~TD_QrySecuDebt_Rsp()
	{

	}
};

//  ��ѯ����ί�������ص�
struct TD_QryMaxEntrustCount_Rsp : TD_Base_Msg
{
	int m_maxStkqty;                    //  ����ί������
	TD_QryMaxEntrustCount_Rsp()
	{
		m_maxStkqty = 0;
	}
	virtual ~TD_QryMaxEntrustCount_Rsp()
	{

	}
};

//  ��ѯ����ȯ�б�ص�
struct TD_QrySecuritiesLendingAmount_Rsp : TD_Base_Msg
{
	GD_CodeType szContractCode;       // ��Ʊ����
	int   m_sepremQty;                // ��ȯ
	TD_QrySecuritiesLendingAmount_Rsp()
	{
		memset(szContractCode, 0, sizeof(GD_CodeType));
		m_sepremQty = 0;
	}
	virtual ~TD_QrySecuritiesLendingAmount_Rsp()
	{

	}
};

//////////////////////////////////////////////////////////////////////////
// ϵͳ����

enum TD_AccountAttr
{
	TD_AccountAttr_noTrading = 0,			//�ǽ���ʵ���˻�
	TD_AccountAttr_productionTrading = 1,	//ʵ�̽����˻�
	TD_AccountAttr_simulationTrading = 2,	//ģ�⽻���˻�
	TD_AccountAttr_testTrading = 3			//���Խ����˻�
};

struct TD_AccountInfo
{
	int nAccountId;					//Id
	char szAccountName[32];			//�˻�����
	char szAccountNo[32];			//�˻���¼��
	TD_AccountAttr nAccountAttr;	//�˻�����  //ʵ���˻���ģ���˻��������˻�

	double nStampTax;			//ӡ��˰
	double nTransferFees;		//������
	double nCommissions;		//Ӷ��
};

struct TD_UserTradeInfoRsp
{
	int nUserId;
	char szUserName[32];					//��¼��
	char szUserNickName[32];				//�û��ǳ�
	char szSecurityCode[32];				//��ȫ��
	
	TD_AccountInfo* m_account;				//ʵ�̽����˻��б��׵�ַ
	int nAccountCount;							//ʵ�̽����˻��б�
}; 


#pragma pack(pop)
#endif //TRADEDATASTRUCT_H