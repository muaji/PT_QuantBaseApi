#ifndef GETDATASTRUCT_H
#define GETDATASTRUCT_H

#pragma pack(push)
#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
//TDF �ṹ��
//////////////////////////////////////////////////////////////////////////
#ifndef __TDF_API_STRUCT_H__
#define __TDF_API_STRUCT_H__
struct TDF_MARKET_CLOSE
{
	char    szMarket[8];        //����������
	int		nTime;				//ʱ��(HHMMSSmmm)
	char	chInfo[64];			//������Ϣ
};

struct TDF_CODE
{
	char szWindCode[32];		//Wind Code: AG1302.SHF
	char szMarket[8];			//market code: SHF
	char szCode[32];			//original code:ag1302
	char szENName[32];
	char szCNName[32];			//chinese name: ����1302
	int nType;
};

struct TDF_OPTION_CODE
{
	TDF_CODE basicCode;

	char szContractID[32];			// ��Ȩ��Լ����
	char szUnderlyingSecurityID[32];//// ���֤ȯ����
	char chCallOrPut;               // �Ϲ��Ϲ�C1        �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
	int  nExerciseDate;             // ��Ȩ��Ȩ�գ�YYYYMMDD

	//�����ֶ�
	char chUnderlyingType;			// ���֤ȯ����C3    0-A�� 1-ETF (EBS �C ETF�� ASH �C A ��)
	char chOptionType;              // ŷʽ��ʽC1        ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��

	char chPriceLimitType;          // �ǵ�����������C1 ��N����ʾ���ǵ�����������, ��R����ʾ���ǵ�����������
	int  nContractMultiplierUnit;	// ��Լ��λ,         ������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
	int  nExercisePrice;            // ��Ȩ��Ȩ��,       ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
	int  nStartDate;                // ��Ȩ�׸�������,YYYYMMDD
	int  nEndDate;                  // ��Ȩ�������/��Ȩ�գ�YYYYMMDD
	int  nExpireDate;               // ��Ȩ�����գ�YYYYMMDD
};

//������Ϣ��MSG_DATA_MARKET ��Ӧ�Ľṹ
struct TDF_MARKET_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //ԭʼCode
	int         nActionDay;             //ҵ������(��Ȼ��)
	int         nTradingDay;            //������
	int			 nTime;					//ʱ��(HHMMSSmmm)
	int			 nStatus;				//״̬
	unsigned int nPreClose;				//ǰ���̼�
	unsigned int nOpen;					//���̼�
	unsigned int nHigh;					//��߼�
	unsigned int nLow;					//��ͼ�
	unsigned int nMatch;				//���¼�
	unsigned int nAskPrice[10];			//������
	unsigned int nAskVol[10];			//������
	unsigned int nBidPrice[10];			//�����
	unsigned int nBidVol[10];			//������
	unsigned int nNumTrades;			//�ɽ�����
	__int64		 iVolume;				//�ɽ�����
	__int64		 iTurnover;				//�ɽ��ܽ��
	__int64		 nTotalBidVol;			//ί����������
	__int64		 nTotalAskVol;			//ί����������
	unsigned int nWeightedAvgBidPrice;	//��Ȩƽ��ί��۸�
	unsigned int nWeightedAvgAskPrice;  //��Ȩƽ��ί���۸�
	int			 nIOPV;					//IOPV��ֵ��ֵ
	int			 nYieldToMaturity;		//����������
	unsigned int nHighLimited;			//��ͣ��
	unsigned int nLowLimited;			//��ͣ��
	char		 chPrefix[4];			//֤ȯ��Ϣǰ׺
	int			 nSyl1;					//��ӯ��1
	int			 nSyl2;					//��ӯ��2
	int			 nSD2;					//����2���Ա���һ�ʣ�
};

//������Ϣ��MSG_DATA_INDEX ��Ӧ�Ľṹ
struct TDF_INDEX_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //ԭʼCode
	int         nActionDay;             //ҵ������(��Ȼ��)
	int         nTradingDay;            //������
	int         nTime;			//ʱ��(HHMMSSmmm)
	int		    nOpenIndex;		//����ָ��
	int 	    nHighIndex;		//���ָ��
	int 	    nLowIndex;		//���ָ��
	int 	    nLastIndex;		//����ָ��
	__int64	    iTotalVolume;	//���������Ӧָ���Ľ�������
	__int64	    iTurnover;		//���������Ӧָ���ĳɽ����
	int		    nPreCloseIndex;	//ǰ��ָ��
};

//������Ϣ��MSG_DATA_FUTURE ��Ӧ�Ľṹ
struct TDF_FUTURE_DATA
{
	char        szWindCode[32];         //600001.SH 
	char        szCode[32];             //ԭʼCode
	int         nActionDay;             //ҵ������(��Ȼ��)
	int         nTradingDay;            //������
	int			 nTime;					//ʱ��(HHMMSSmmm)	
	int			 nStatus;				//״̬
	__int64		 iPreOpenInterest;		//��ֲ�
	unsigned int nPreClose;				//�����̼�
	unsigned int nPreSettlePrice;		//�����
	unsigned int nOpen;					//���̼�	
	unsigned int nHigh;					//��߼�
	unsigned int nLow;					//��ͼ�
	unsigned int nMatch;				//���¼�
	__int64		 iVolume;				//�ɽ�����
	__int64		 iTurnover;				//�ɽ��ܽ��
	__int64		 iOpenInterest;			//�ֲ�����
	unsigned int nClose;				//������
	unsigned int nSettlePrice;			//�����
	unsigned int nHighLimited;			//��ͣ��
	unsigned int nLowLimited;			//��ͣ��
	int			 nPreDelta;			    //����ʵ��
	int			 nCurrDelta;            //����ʵ��
	unsigned int nAskPrice[5];			//������
	unsigned int nAskVol[5];			//������
	unsigned int nBidPrice[5];			//�����
	unsigned int nBidVol[5];			//������

	//Add 20140605
	int	lAuctionPrice;		//�������жϲο���
	int	lAuctionQty;		//�������жϼ��Ͼ�������ƥ����
};

//������Ϣ��MSG_DATA_ORDERQUEUE ��Ӧ�Ľṹ
struct TDF_ORDER_QUEUE
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //ԭʼCode
	int     nActionDay;     //��Ȼ��
	int 	nTime;			//ʱ��(HHMMSSmmm)
	int     nSide;			//��������('B':Bid 'A':Ask)
	int		nPrice;			//ί�м۸�
	int 	nOrders;		//��������
	int 	nABItems;		//��ϸ����
	int 	nABVolume[200];	//������ϸ
};

//������Ϣ��MSG_DATA_TRANSACTION ��Ӧ�Ľṹ
struct TDF_TRANSACTION
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //ԭʼCode
	int     nActionDay;     //��Ȼ��
	int 	nTime;		    //�ɽ�ʱ��(HHMMSSmmm)
	int 	nIndex;		    //�ɽ����
	int		nPrice;		    //�ɽ��۸�
	int 	nVolume;	    //�ɽ�����
	int		nTurnover;	    //�ɽ����
	int     nBSFlag;        //��������(��'B', ����'A', ������' ')
	char    chOrderKind;    //�ɽ����
	char    chFunctionCode; //�ɽ�����
	int	    nAskOrder;	    //������ί�����
	int	    nBidOrder;	    //����ί�����
};

//������Ϣ��MSG_DATA_ORDER ��Ӧ�Ľṹ
struct TDF_ORDER
{
	char    szWindCode[32]; //600001.SH 
	char    szCode[32];     //ԭʼCode
	int 	nActionDay;	    //ί������(YYMMDD)
	int 	nTime;			//ί��ʱ��(HHMMSSmmm)
	int 	nOrder;	        //ί�к�
	int		nPrice;			//ί�м۸�
	int 	nVolume;		//ί������
	char    chOrderKind;	//ί�����
	char    chFunctionCode;	//ί�д���('B','S','C')
};
#endif // __TDF_API_STRUCT_H__

typedef char GD_CodeType[32];
typedef char GD_CodeName[32];
typedef char GD_ISODateTimeType[21];	//���ں�ʱ������(��ʽ yyyy-MM-dd hh:mm:ss)
typedef char GD_ShortText[128];
typedef char GD_Text[1024];

enum GD_TimelinessType				//����Ч��
{
	historyData_GD_TimelinessType,		//��ʷ����
	realtimeData_GD_TimelinessType		//ʵʱ����
};

enum GD_StockType{
	stock_GD_StockType = 0,			//��Ʊ
	index_GD_StockType,				//ָ��
	future_GD_StockType,			//�ڻ�
	option_GD_StockType,			//��Ȩ

	none_GD_StockType = -1
};

enum GD_CycType				//
{
	none_GD_CycType			= 0x0000,		//��
	second_10_GD_CycType	= 0x0001,		//10��
	minute_GD_CycType		= 0x0002,		//��
	minute_5_GD_CycType		= 0x0004,		//5��
	minute_15_GD_CycType	= 0x0008,		//15��
	minute_30_GD_CycType	= 0x0010,		//30��
	hour_GD_CycType			= 0x0020,		//Сʱ
	day_GD_CycType			= 0x0040,		//��
};

enum GD_UpdateSubCodeType
{
	add_GD_UpdateSubCodeType = 0,		//��Ӷ��Ĵ���
	remove_GD_UpdateSubCodeType,		//�Ƴ����ж��Ĵ���
	replace_GD_UpdateSubCodeType		//�滻ȫ�����Ĵ���
};

enum GD_ServerType		//��������������
{
	realTime_GD_ServerType = 0,			//ʵʱ���������
	simulation_GD_ServerType,			//ģ�����������
	history_GD_ServerType				//��ʷ���ݷ�����
};

enum GD_PlaybackSpeedType	//������ʷ����ģ��ز�����
{
	fast_GD_PlaybackSpeedType,				//����ģʽ
	normal_GD_PlaybackSpeedType,			//����ģʽ
	x2Spped_GD_PlaybackSpeedType,			//2����ģʽ
	x3Spped_GD_PlaybackSpeedType,			//3����ģʽ
	x5Spped_GD_PlaybackSpeedType,			//5����ģʽ
	x10Spped_GD_PlaybackSpeedType			//10����ģʽ
};

enum GD_SubDataType		//������������
{
	all_GD_SubDataType			= 0x0000,	//������������
	market_GD_SubDataType		= 0x0001,	//��������
	transaction_GD_SubDataType	= 0x0002,	//��ʳɽ�����
	orderQueue_GD_SubDataType	= 0x0004,	//ί�ж�������
	order_GD_SubDataType		= 0x0008,	//���ί������
};

enum GD_ListStatusType	//����״̬
{
	ALL_GD_ListStatusType,	//����
	L_GD_ListStatusType,	//����
	S_GD_ListStatusType,	//��ͣ
	DE_GD_ListStatusType,	//��ֹ����
	UN_GD_ListStatusType,	//δ����
};

//��Ʊ�������
typedef char GD_EquTypeCD;
const GD_EquTypeCD		Whole_GD_EquTypeCD = 'W';	//ȫ��
const GD_EquTypeCD		A_GD_EquTypeCD = 'A';		//A��
const GD_EquTypeCD		B_GD_EquTypeCD = 'B';		//B��

struct GD_StockBaseInfo	//��Ʊ������Ϣ 
{
	GD_CodeType szWindCode;				//֤ȯ����
	GD_ShortText szListSector;			//���а��
	GD_ShortText szTransCurrCD;			//���׻���
	GD_ShortText szSecShortName;		//֤ȯ���
	GD_ShortText szSecFullName;			//ȫ��
	GD_ListStatusType nListStatusCD;	//����״̬
	GD_ISODateTimeType szListDate;		//��������
	GD_ISODateTimeType szDelistDate;	//ժ������
	GD_EquTypeCD szEquTypeCD;			//��Ʊ�������
	GD_ShortText szEquType;				//��Ʊ���
	int			nPartyId;				//�����ڲ�ID
	double		nTotalShares;			//�ܹɱ������£�
	double		nNonrestFloatShares;	//��˾��������ͨ�ɷ��ϼƣ����£�
	double		nNonrestFloatA;			//��������ͨ�ɱ�(����)�����ΪA�ɣ�����Ϊ������������ͨA�ɹɱ����������ΪB�ɣ�����Ϊ������ͨB�ɹɱ�����
	GD_ShortText szOfficeAddr;			//�칫��ַ
	GD_Text		szPrimeOperating;		//��Ӫҵ��Χ
	GD_ISODateTimeType szFinancialReportDate;		//���񱨸�����
	double		nTShEquity;				//������Ȩ��ϼ�
};

struct GD_RestorationFactor				//��Ȩ����
{
	GD_CodeType szWindCode;				//֤ȯ����
	GD_ISODateTimeType szExDivDate;		//��Ȩ��Ϣ��
	double nPerCashDiv;					//ÿ������
	double nPerShareDivRatio;			//ÿ���͹ɱ���
	double nPerShareTransRatio;			//ÿ��ת���ɱ���
	double nAllotmentRatio;				//ÿ����ɱ���
	double nAllotmentPrice;				//��ɼ�
	double nRestorationFactor;			//��Ȩ����(ǰ��Ȩ)
	double nAccumRestorationFactor;		//�ۻ���Ȩ����
	GD_ISODateTimeType szEndDate;		//�ۻ���Ȩ���ӽ�ֹ����
};

struct GD_DetailMarketDayKline			//��ϸ��k��
{
	GD_CodeType szWindCode;				//֤ȯ����
	GD_ISODateTimeType szTradeDate;		//������
	char szCodeCNName[32];				//֤ȯ������
	double nPreClose;					//�����̣��������������ĸ�Ȩǰ��
	double nActPreClose;				//ʵ��������
	double nOpen;						//����
	double nHigh;						//��߼�
	double nLow;						//��ͼ�
	double nClose;						//������
	double nVolume;						//�ɽ���
	double nTurover;					//�ɽ����
	unsigned int nDealAmount;			//�ɽ�����
	double nTurnoverRate;				//�ջ�����
	double nAccumRestorationFactor;		//�ۼ�ǰ��Ȩ���� ǰ��Ȩ�Ƕ���ʷ������е�������Ȩ��Ϣ�յ����鲻�ܱ��γ�Ȩ��ϢӰ�죬������е���������һ�γ�Ȩ��Ϣ�������������ڼ�ļ۸���Ҫ�����κεĵ��������ڼ�ǰ��Ȩ���Ӷ���1��
	double nNegMarketValue;				//��ͨ��ֵ
	double nMarketValue;				//����ֵ
	double nChgPct;						//�ǵ���
	bool bIsOpen;						//�Ƿ��̣� false δ���̣�true ����
};

struct GD_StockFactors					//��Ʊ����
{
	GD_CodeType szWindCode;						//֤ȯ����
	GD_ISODateTimeType szTradeDate;				//������

	std::map<std::string, double> m_factors;
	/* factor key ˵��
	ACD20							double	20���ռ��ɷ�ָ�꣨Accumulative Distribution�������г���Ϊ�����ռ������룩���ɷ��������������������ھ��������ӡ�
	ACD6							double	6���ռ��ɷ�ָ�꣨Accumulative Distribution�������г���Ϊ�����ռ������룩���ɷ��������������������ھ���������
	AD								double	�ۻ�/�ɷ��ߣ�Accumulation / Distribution Line����ָ�꽫ÿ�յĳɽ���ͨ���۸��Ȩ�ۼƣ����Լ���ɽ����Ķ�������������������
	AD20							double	�ۻ�/�ɷ��ߣ�Accumulation / Distribution Line����ָ�꽫ÿ�յĳɽ���ͨ���۸��Ȩ�ۼƣ����Լ���ɽ����Ķ�������������������
	AD6								double	�ۻ�/�ɷ��ߣ�Accumulation / Distribution Line����ָ�꽫ÿ�յĳɽ���ͨ���۸��Ȩ�ۼƣ����Լ���ɽ����Ķ�������������������
	ADTM							double	��̬������ָ�꣬�ÿ��̼۵����ϲ������Ⱥ����²������ȵľ����ֵ�����������ߵ͵�ָ�ꡣ���ڳ����������ӡ�
	ADX								double	ƽ������ָ����DMI���ӵĹ��ɲ��֡���������������
	ADXR							double	���ƽ������ָ����DMI���ӵĹ��ɲ��֡���������������
	APBMA							double	����ƫ���ƶ�ƽ����Absolute Price Bias Moving Average��������һ��ʱ���ڼ۸�ƫ����ߵ��ƶ�ƽ�������ھ��������ӡ�
	AR								double	����ָ�꣬���Ե��쿪�м�Ϊ���������Ե����м۷ֱ�Ƚϵ�����ߣ���ͼۣ�ͨ��һ��ʱ���ڿ��м��ڹɼ��еĵ�λ����ӳ�г������������������������ӡ�
	ARBR							double	����ָ�꣨AR������Ըָ�꣨BR�������Է�����ʷ�ɼ�Ϊ�ֶεļ���ָ�꣬ARBRʹ��AR��ȥBR�õ���ֵ���������������ӡ�
	ARC								double	�仯��ָ����ֵ����Ʊ�ļ۸�仯��RCָ��ľ�ֵ�������ж�ǰһ�ν��������ڹ�Ʊ��ƽ���۸�仯�ʡ����ڳ����������ӡ�
	Aroon							double	Aroonͨ�������Լ۸�ﵽ�������ֵ�����ֵ�������������ڼ���������Ͷ����Ԥ��֤ȯ�۸�����Ƶ����������ת�ı仯��Aroonָ���ΪAroon��AroonUp��AroonDown3������ָ�ꡣ��������������
	AroonDown						double	����Aroon���ӵ��м��������������������
	AroonUp							double	����Aroon���ӵ��м��������������������
	ASI								double	�ۼ�������ָ�꣨Accumulation Swing Index�����ֳ�ʵ���ߣ�ASI��ͼ�Կ��̡���ߡ���͡����̼۹�����һ�������ߣ��Ա�ȡ��Ŀǰ�����ƣ��γ����ܱ��ֵ�ǰ�п�����ʵ�г��ߣ�Real Market����
	ATR14							double	14�վ���ָ�꣨Average TRUE Ranger����ȡһ��ʱ�������ڵĹɼ۲������ȵ��ƶ�ƽ��ֵ������ʾ�г��仯�ʵ�ָ�꣬��Ҫ������������ʱ�������ڳ����������ӡ�
	ATR6							double	6�վ���ָ�꣨Average TRUE Ranger����ȡһ��ʱ�������ڵĹɼ۲������ȵ��ƶ�ƽ��ֵ������ʾ�г��仯�ʵ�ָ�꣬��Ҫ������������ʱ�������ڳ����������ӡ�
	BBI								double	���ָ����Bull and Bear Index������һ�ֽ���ͬ�����ƶ�ƽ���߼�Ȩƽ��֮����ۺ�ָ�ꡣ���ھ��������ӡ�
	BBIC							double	����BBI�������̼۵õ������ھ��������ӡ�
	BearPower						double	��ͷ�������Ǽ���Elder���ӵ��м�������������������ӡ�
	BIAS10							double	10�չ����ʣ����Yֵ�����ƶ�ƽ��ԭ��������һ���ָ�꣬��ʾ�ɼ�ƫ������ָ��ն�ٷֱ�ֵ�����ڳ����������ӡ�
	BIAS20							double	20�չ����ʣ����Yֵ�����ƶ�ƽ��ԭ��������һ���ָ�꣬��ʾ�ɼ�ƫ������ָ��ն�ٷֱ�ֵ�����ڳ����������ӡ�
	BIAS5							double	5�չ����ʣ����Yֵ�����ƶ�ƽ��ԭ��������һ���ָ�꣬��ʾ�ɼ�ƫ������ָ��ն�ٷֱ�ֵ�����ڳ����������ӡ�
	BIAS60							double	60�չ����ʣ����Yֵ�����ƶ�ƽ��ԭ��������һ���ָ�꣬��ʾ�ɼ�ƫ������ָ��ն�ٷֱ�ֵ�����ڳ����������ӡ�
	BollDown						double	�¹��ߣ������ߣ�ָ�꣨Bollinger Bands�����������йɼ��˶����Ƶ�һ���г��ڼ����������ߡ����ڳ����������ӡ�
	BollUp							double	�Ϲ��ߣ������ߣ�ָ�꣨Bollinger Bands�����������йɼ��˶����Ƶ�һ���г��ڼ����������ߡ����ڳ����������ӡ�
	BR								double	��Ըָ�꣬�����������м�Ϊ�������ֱ��뵱����ߣ���ͼ���ȣ�ͨ��һ��ʱ���������ڹɼ��еĵ�λ����ӳ�г�������Ը�ĳ̶ȡ��������������ӡ�
	BullPower						double	��ͷ�������Ǽ���Elder���ӵ��м�������������������ӡ�
	CCI10							double	10��˳��ָ�꣨Commodity Channel Index����ר�Ų����ɼ��Ƿ��ѳ�����̬�ֲ���Χ�����ڳ����������ӡ�
	CCI20							double	20��˳��ָ�꣨Commodity Channel Index����ר�Ų����ɼ��Ƿ��ѳ�����̬�ֲ���Χ�����ڳ����������ӡ�
	CCI5							double	5��˳��ָ�꣨Commodity Channel Index����ר�Ų����ɼ��Ƿ��ѳ�����̬�ֲ���Χ�����ڳ����������ӡ�
	CCI88							double	88��˳��ָ�꣨Commodity Channel Index����ר�Ų����ɼ��Ƿ��ѳ�����̬�ֲ���Χ�����ڳ����������ӡ�
	ChaikinOscillator				double	����ָ�꣨Chaikin Oscillator������ָ�����AD���ߵ�ָ���ƶ����߶�����õ�����������������
	ChaikinVolatility				double	������ɢָ�꣨Chaikin Volatility�����CVLT��VCI��CV�����ֳơ����������ָ��������ͨ������һ��ʱ���ڼ۸����ƽ��ֵ�ı仯����ӳ�۸����ɢ�̶ȡ���������������
	ChandeSD						double	����CMO���ӵ��м������SD�ǽ������̼����������̼ۣ��µ��գ���ֵ�ľ���ֵ���ܡ����������ǣ�������ֵΪ0�����ڳ����������ӡ�
	ChandeSU						double	����CMO���ӵ��м������SU�ǽ������̼����������̼ۣ������գ���ֵ���ܡ��������µ���������ֵΪ0�����ڳ����������ӡ�
	CMO								double	Ǯ�¶����ڶ�ָ�꣨Chande Momentum Osciliator��������������ָ��ڶ�ָ�������ǿ��ָ�꣨RSI�������ָ�꣨KDJ����ͬ��Ǯ�¶���ָ���ڼ��㹫ʽ�ķ����в��������պ��µ��յ����ݡ����ڳ����������ӡ�
	CoppockCurve					double	����ָ�꣨Coppock Curve�����ֳơ��������ߡ�����ָ��ͨ�������¶ȼ۸�ı仯���ʵļ�Ȩƽ��ֵ�������г��Ķ��������ڳ���ָ�꣬�������Ǹ�Ϊ�ռ��ָ�ꡣ��������������
	CR20							double	CRָ������һ���������ڣ�����Ϊ20�գ����м�۱Ƚϵ�ǰ���ڵ���߼ۡ���ͼۣ������һ��ʱ���ڹɼ۵ġ�ǿ�������������������ӡ�
	DBCD							double	��ͬ�������ʣ��ȼ��������BIAS��Ȼ����㲻ͬ�յĹ�����֮���������������ָ���ƶ�ƽ�������ŵ����ܹ�����ָ��Ľ���ͬ�������������⻬���ź���ȷ���ܹ���Ч�Ĺ��˵�α�źš����ڳ����������ӡ�
	DDI								double	�����׼���ָ�����۲�һ��ʱ���ڹɼ������ǰһ�����ϲ��������²����ı���������������ƶ�ƽ��������DDIָ����������ʾһ�ֳ��������Ƶķ���ı䡣��������������
	DEA								double	����MACD���ӵ��м��������������������
	DIF								double	����DDI���ӵ��м��������������������
	DIFF							double	����MACD���ӵ��м��������������������
	DIZ								double	����DDI���ӵ��м��������������������
	DownRVI							double	����RVI���ӵ��м���������ڳ����������ӡ�
	Elder							double	����͸��ָ�꣨Elder-ray Index���������߿��Ծ��ɸ�ָ�꣬�۲��г�����֮�µĶ�ͷ���ͷ�������������������ӡ�
	EMA12							double	12��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMA26							double	26��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMV14							double	���ײ���ָ�꣨Ease of Movement Value����EMV���۸���ɽ����ı仯��ϳ�һ������ָ������ӳ�ɼۻ�ָ���ı䶯״�������ڹɼ۵ı仯�ͳɽ����ı仯������������ָ����ֵ�ı䶯��EMVʵ����Ҳ��һ�����ۺϳ�ָ�ꡣ��������������
	EMV6							double	���ײ���ָ�꣨Ease of Movement Value����EMV���۸���ɽ����ı仯��ϳ�һ������ָ������ӳ�ɼۻ�ָ���ı䶯״�������ڹɼ۵ı仯�ͳɽ����ı仯������������ָ����ֵ�ı䶯��EMVʵ����Ҳ��һ�����ۺϳ�ָ�ꡣ��������������
	Hurst							double	��˹��ָ����Hurst exponent��������Ӣ��ˮ��ר��H��E��Hurst��������ر꼫��(R/S)����������������˹��ָ��(H)����Ϊ�ж�ʱ�������������������߻�����ƫ��������߹��̵�ָ�ꡣ��������������
	JDQS20							double	�׶�ǿ��ָ�꣬��ָ�����һ������N���ڣ������µ�ʱ���������ǵı������������������ӡ�
	KDJ_D							double	���ָ�ꡣ���ۺ��˶������ǿ��ָ�꼰�ƶ�ƽ���ߵ��ŵ㣬���������ɼ�����۸�������Χ�ı���̶ȡ����ڳ����������ӡ�
	KDJ_J							double	���ָ�ꡣ���ۺ��˶������ǿ��ָ�꼰�ƶ�ƽ���ߵ��ŵ㣬���������ɼ�����۸�������Χ�ı���̶ȡ����ڳ����������ӡ�
	KDJ_K							double	���ָ�ꡣ���ۺ��˶������ǿ��ָ�꼰�ƶ�ƽ���ߵ��ŵ㣬���������ɼ�����۸�������Χ�ı���̶ȡ����ڳ����������ӡ�
	KlingerOscillator				double	�ɽ����ڶ�ָ�꣬��ָ���ھ��������ʽ��������Ƶ�ͬʱ�����˶��ڶ����ʽ������������ԣ������������Ԥ����ڼ۸�յ㡣���ڳɽ���������
	MA10Close						double	���߼۸�ȡ����ڹ�Ʊ�ĳɽ��۸���������߻ع�����ƣ�������߼۸�ȿ���Ԥ���Ʊ��δ�����ڵ��˶����ơ����ھ��������ӡ�
	MA10RegressCoeff12				double	10�ռ۸�ƽ����12�����Իع�ϵ������������������
	MA10RegressCoeff6				double	10�ռ۸�ƽ����6�����Իع�ϵ������������������
	MassIndex						double	÷˹�ߣ�Mass Index������ָ����Donald Dorsey�ۻ��ɼ۲������֮������Ƶ������ߡ�������Ҫ�����ã�����Ѱ����ǹɻ��߼������ƹɵ���Ҫ���Ʒ�ת�㡣�������������ӡ�
	minusDI							double	�½�ָ�꣬DMI���ӵĹ��ɲ��֡���������������
	MoneyFlow20						double	20���ʽ������������̼ۡ���߼ۼ���ͼ۵ľ�ֵ���Ե��ճɽ������ɵõ��ý����յ��ʽ����������ڳɽ���������
	MTM								double	����ָ�꣨Momentom Index��������ָ���Է����ɼ۲������ٶ�ΪĿ�ģ��о��ɼ��ڲ��������и��ּ��٣����٣����������Լ��ɼ��ɾ��������ɶ�ת����������������������
	MTMMA							double	����MTM��10�վ�ֵ����������������
	NVI								double	���ɽ���ָ�꣨Negative Volume Index������ָ�����Ҫ�����Ǳ��Ŀǰ�г������Ǵ��ڶ�ͷ���黹�ǿ�ͷ���飬��׷���г��ʽ������������������ӡ�
	OBV								double	������ָ�꣨On Balance Volume��OBV�����Թ��еĳɽ����仯���������е��ƶ������Ӷ����йɼ۵����ơ����ڳɽ���������
	OBV20							double	20��������ָ�꣨On Balance Volume��OBV�����Թ��еĳɽ����仯���������е��ƶ������Ӷ����йɼ۵����ơ����ڳɽ���������
	OBV6							double	6��������ָ�꣨On Balance Volume��OBV�����Թ��еĳɽ����仯���������е��ƶ������Ӷ����йɼ۵����ơ����ڳɽ���������
	PLRC12							double	12�����̼۸�۸����Իع�ϵ����Price Linear Regression Coefficient������������������
	PLRC6							double	6�����̼۸����Իع�ϵ����Price Linear Regression Coefficient������������������
	plusDI							double	����ָ�꣬DMI���ӵĹ��ɲ��֡���������������
	PVI								double	���ɽ���ָ�꣨Positive Volume Index������ָ�����Ҫ�����Ǳ��Ŀǰ�г������Ǵ��ڶ�ͷ���黹�ǿ�ͷ���飬��׷���г��ʽ������������������ӡ�
	PVT								double	�������ƣ�Price and Volume Trend��ָ�꣬�������仯��۸������л�����ϵ����һ�𣬴Ӷ���������������ָ�ꡣ��������������
	PVT12							double	����PVT��12�վ�ֵ����������������
	PVT6							double	����PVT��6�վ�ֵ����������������
	RC12							double	12�ձ仯��ָ����Rate of Change���������ڶ���ָ��������۸�ʼ���������ģ���仯��ָ��ʼ����100%�����ϣ�������仯�ٶ�ָ�������Ϸ�չʱ��˵���۸��������ٶ��ڼӿ졣�������������ӡ�
	RC24							double	24�ձ仯��ָ����Rate of Change���������ڶ���ָ��������۸�ʼ���������ģ���仯��ָ��ʼ����100%�����ϣ�������仯�ٶ�ָ�������Ϸ�չʱ��˵���۸��������ٶ��ڼӿ졣�������������ӡ�
	ROC20							double	6�ձ䶯���ʣ�Price Rate of Change�����Ե��յ����̼ۺ�N��ǰ�����̼۱Ƚϣ�ͨ������ɼ�ĳһ��ʱ�������̼۱䶯�ı�����Ӧ�ü۸���ƶ��Ƚ���������λ���������ڳ����������ӡ�
	ROC6							double	6�ձ䶯���ʣ�Price Rate of Change�����Ե��յ����̼ۺ�N��ǰ�����̼۱Ƚϣ�ͨ������ɼ�ĳһ��ʱ�������̼۱䶯�ı�����Ӧ�ü۸���ƶ��Ƚ���������λ���������ڳ����������ӡ�
	RVI								double	�����ɢָ����Relative Volatility Index�����ֳơ���Բ�����ָ�ꡱ�����ڲ����۸�ķ�ɢ���ƣ���Ҫ����������ȷ��ָ�꣬����Ͼ���ϵͳ������ָ�����������ָ��ʹ�á����ڳ����������ӡ�
	SBM								double	����ADTM���ӵ��м���������ڳ����������ӡ�
	SRMI							double	��������ָ�ꡣ���ڳ����������ӡ�
	STM								double	����ADTM���ӵ��м���������ڳ����������ӡ�
	SwingIndex						double	������ָ�꣬����ASI���ӵ��м��������������������
	TEMA10							double	10������ָ���ƶ�ƽ���ߣ�Triple Exponential Moving Average����ȡʱ��N�ڵ����̼۷ֱ������һ������ָ����Ȩƽ�������ھ��������ӡ�
	TEMA5							double	5������ָ���ƶ�ƽ���ߣ�Triple Exponential Moving Average����ȡʱ��N�ڵ����̼۷ֱ������һ������ָ����Ȩƽ�������ھ��������ӡ�
	TRIX10							double	10�����̼�����ָ��ƽ���ƶ�ƽ��ָ�꣨Triple Exponentially Smoothed Average����TRIX�����ƶ�ƽ�������ۣ���һ��ƽ���߽�������ƽ�������ٸ��������ƶ�ƽ���ߵı䶯�����Ԥ��ɼ۵ĳ������ơ���������������
	TRIX5							double	5�����̼�����ָ��ƽ���ƶ�ƽ��ָ�꣨Triple Exponentially Smoothed Average����TRIX�����ƶ�ƽ�������ۣ���һ��ƽ���߽�������ƽ�������ٸ��������ƶ�ƽ���ߵı䶯�����Ԥ��ɼ۵ĳ������ơ���������������
	TVMA20							double	20�ճɽ������ƶ�ƽ��ֵ��Turnover Value Moving Average�������ڳɽ���������
	TVMA6							double	6�ճɽ������ƶ�ƽ��ֵ��Turnover Value Moving Average�������ڳɽ���������
	TVSTD20							double	20�ճɽ����ı�׼�Turnover Value Standard Deviation�������ڳɽ���������
	TVSTD6							double	20�ճɽ����ı�׼�Turnover Value Standard Deviation�������ڳɽ���������
	Ulcer10							double	��Peter Martin��1987�������1989�귢����Peter Martin��Byron McCann������The Investors Guide to Fidelity Funds�����ڿ������µĲ����ԡ���������������
	Ulcer5							double	��Peter Martin��1987�������1989�귢����Peter Martin��Byron McCann������The Investors Guide to Fidelity Funds�����ڿ������µĲ����ԡ���������������
	UOS								double	�ռ�ָ�꣨Ultimate Oscillator��������ʹ�õĸ�����ָ�꣬�������ڲ�����ѡ���൱���У���ͬ�п�����ͬ�����趨����ָ�꣬�����Ľ����Ȼ��ͬ����ˣ�ѡ����ѵĲ�����ϣ���Ϊʹ����ָ��֮ǰ����Ҫ��һ����������������������
	UpRVI							double	����RVI���ӵ��м���������ڳ����������ӡ�
	VDEA							double	����VMACD���ӵ��м������Volume Difference Exponential Average�������ڳɽ���������
	VDIFF							double	����VMACD���ӵ��м���������ڳɽ���������
	VEMA10							double	�ɽ�����10��ָ���ƶ�ƽ�������ڳɽ���������
	VEMA12							double	�ɽ�����12��ָ���ƶ�ƽ�������ڳɽ���������
	VEMA26							double	�ɽ�����26��ָ���ƶ�ƽ�������ڳɽ���������
	VEMA5							double	�ɽ�����5��ָ���ƶ�ƽ�������ڳɽ���������
	VMACD							double	�ɽ�����ָ��ƽ����ͬ�ƶ�ƽ���ߣ�Volume Moving Average Convergence and Divergence����VMACD�������MACD������ͬ, ��VMACDȡ�õ�����Դ�ǳɽ�����MACDȡ�õ�����Դ�ǳɽ��۸����ڳɽ���������
	VOSC							double	�ɽ����𵴣�Volume Oscillator�����ֳ��ƶ�ƽ���ɽ���ָ�꣬�������ǽ�������ɽ������ƶ�ƽ���ߣ�����ͨ���Գɽ����ĳ����ƶ�ƽ���ߺͶ����ƶ�ƽ����֮��ıȽϣ������ɽ������������ƺͼ�ʱ��������ת�䷽�����ڳɽ���������
	VR								double	�ɽ������ʣ�Volume Ratio����ͨ�������ɼ������ճɽ����ɽ�������ͬ����ɼ��½��ճɽ����ֵ���Ӷ������г��������Ƶ����ڼ���ָ�ꡣ���ڳɽ���������
	VROC12							double	12�����䶯����ָ�꣨Volume Rate of Change�����Խ���ĳɽ�����N��ǰ�ĳɽ����Ƚϣ�ͨ������ĳһ��ʱ���ڳɽ����䶯�ķ��ȣ�Ӧ�óɽ������ƶ��Ƚ��������ɽ����˶����򣬴ﵽ����̽��ɽ��������ǿ�������������ɽ����ķ�չ���Ƽ��佫���Ƿ���ת�Ƶ���Ը�����ڳɽ����ķ�����ָ�ꡣ���ڳɽ���������
	VROC6							double	6�����䶯����ָ�꣨Volume Rate of Change�����Խ���ĳɽ�����N��ǰ�ĳɽ����Ƚϣ�ͨ������ĳһ��ʱ���ڳɽ����䶯�ķ��ȣ�Ӧ�óɽ������ƶ��Ƚ��������ɽ����˶����򣬴ﵽ����̽��ɽ��������ǿ�������������ɽ����ķ�չ���Ƽ��佫���Ƿ���ת�Ƶ���Ը�����ڳɽ����ķ�����ָ�ꡣ���ڳɽ���������
	VSTD10							double	10�ճɽ�����׼�Volume Standard Deviation��������ɽ����Ĳ����̶ȡ����ڳɽ���������
	VSTD20							double	20�ճɽ�����׼�Volume Standard Deviation��������ɽ����Ĳ����̶ȡ����ڳɽ���������
	AccountsPayablesTDays			double	Ӧ���˿���ת������Accounts payable turnover days�������㷽����Ӧ���˿���ת����=360/Ӧ���˿���ת�ʡ�����Ӫ�����������ӡ�
	AccountsPayablesTRate			double	Ӧ���˿���ת�ʣ�Accounts payable turnover rate�������㷽����Ӧ���˿���ת��=Ӫҵ�ɱ���TTM��/Ӧ���˿�+Ӧ��Ʊ��+Ԥ���������Ӫ�����������ӡ�
	AdminiExpenseRate				double	���������Ӫҵ������֮�ȣ�Administrative expense rate�������㷽�������������Ӫҵ������֮��=������ã�TTM��/Ӫҵ�����루TTM��������ӯ���������������������ӡ�
	ARTDays							double	Ӧ���˿���ת������Accounts receivable turnover days�������㷽����Ӧ���˿���ת����=360/Ӧ���˿���ת�ʡ�����Ӫ�����������ӡ�
	ARTRate							double	Ӧ���˿���ת�ʣ�Accounts receivable turnover rate�������㷽����Ӧ���˿���ת��=Ӫҵ���루TTM��/Ӧ���˿�+Ӧ��Ʊ��+Ԥ���˿����Ӫ�����������ӡ�
	ASSI							double	�������ʲ���Natural logarithm of total assets�������㷽�����������ʲ�=���ʲ��Ķ��������ڹ�ֵ����ֵ�����ӡ�
	BLEV							double	����ܸˣ�Book leverage�������㷽��������ܸ�=��������ծ�ϼ�/�ɶ�Ȩ�档���ڳ�ծ�������ʱ��ṹ�����ӡ�
	BondsPayableToAsset				double	Ӧ��ծȯ�����ʲ�֮�ȣ�Bonds payable to total assets�������㷽����Ӧ��ծȯ�����ʲ�֮��=Ӧ��ծȯ/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	CashRateOfSales					double	��Ӫ��������ֽ�����������Ӫҵ����֮�ȣ�Cash rate of sales�������㷽������Ӫ��������ֽ�����������Ӫҵ����֮��=��Ӫ��������ֽ��������TTM��/Ӫҵ���루TTM���������ֽ���ָ�����ӡ�
	CashToCurrentLiability			double	�ֽ���ʣ�Cash to current liability�������㷽�����ֽ����=��ĩ�ֽ��ֽ�ȼ�����TTM��/������ծ�ϼơ������ֽ���ָ�����ӡ�
	CMRA							double	24 ���ۼ����棨Monthly cumulative return range over the past 24 months�������ڳ����������ӡ�
	CTOP							double	�ֽ�����ֵ�ȣ�Cash flow to price�������㷽�����ֽ�����ֵ��=ÿ�����֣�˰ǰ�����ֺ�ǰ�ܹɱ�/����ֵ�������ֽ���ָ�����ӡ�
	CTP5							double	5��ƽ���ֽ�����ֵ�ȣ�Five-year average cash flow to price�������㷽����5��ƽ���ֽ�����ֵ��=������ÿ�����֣�˰ǰ�����ֺ�ǰ�ܹɱ�/����������ֵ�������ֽ���ָ�����ӡ�
	CurrentAssetsRatio				double	�����ʲ����ʣ�Current assets ratio�������㷽���������ʲ�����=�����ʲ��ϼ�/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	CurrentAssetsTRate				double	�����ʲ���ת�ʣ�Current assets turnover rate�����㷽���������ʲ���ת��=Ӫҵ���루TTM��/�����ʲ��ϼơ�����Ӫ�����������ӡ�
	CurrentRatio					double	�������ʣ�Current ratio�������㷽������������=�����ʲ��ϼ�/������ծ�ϼơ����ڳ�ծ�������ʱ��ṹ�����ӡ�
	DAVOL10							double	10��ƽ����������120��ƽ�������ʣ�Turnover Rate��֮�ȡ����ڳɽ���������
	DAVOL20							double	20��ƽ����������120��ƽ�������ʣ�Turnover Rate��֮�ȡ����ڳɽ���������
	DAVOL5							double	5��ƽ����������120��ƽ�������ʣ�Turnover Rate��֮�ȡ����ڳɽ���������
	DDNBT							double	�µ�������Downside beta��������12 �����У��г����������Ϊ��ʱ����������������г����������Ļع�ϵ�������ڳ����������ӡ�
	DDNCR							double	�µ����ϵ����Downside correlation��������12�����У��г����������Ϊ��ʱ����������������г��������������ϵ�������ڳ����������ӡ�
	DDNSR							double	�µ�������Downside standard deviations ratio��������12�����У��г����������Ϊ��ʱ�������������׼����г�����������׼��֮�ȡ����ڳ����������ӡ�
	DebtEquityRatio					double	��Ȩ���ʣ�Debt equity ratio�������㷽������Ȩ����=��ծ�ϼ�/����ĸ��˾������Ȩ��ϼơ����ڳ�ծ�������ʱ��ṹ�����ӡ�
	DebtsAssetRatio					double	ծ�����ʲ��ȣ�Debt to total assets�������㷽����ծ�����ʲ���=��ծ�ϼ�/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	DHILO							double	������λ����median of volatility����ÿ�ն�����߼ۺͶ�����ͼ۲�ֵ��3������λ������������������
	DilutedEPS						double	ϡ��ÿ�����棨Diluted earnings per share��������ÿ��ָ������
	DVRAT							double	������Բ�����Daily returns variance ratio-serial dependence in daily returns�������ڳ����������ӡ�
	EBITToTOR						double	Ϣ˰ǰ������Ӫҵ������֮�ȡ����㷽��: Ϣ˰ǰ������Ӫҵ������֮��=(�����ܶ�+��Ϣ֧��-��Ϣ����)/ Ӫҵ�����룬���û����Ϣ֧�����ò�����ô��棬���Ͽ�Ŀʹ�õĶ���TTM����ֵ������ӯ���������������������ӡ�
	EGRO							double	5�����������ʣ�Five-year earnings growth�������㷽����5 ������������= 5���������ʱ�䣨�꣩�������Իع�Ļع�ϵ��/5 �������ֵ�ľ���ֵ������ӯ���������������������ӡ�
	EMA10							double	10��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMA120							double	120��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMA20							double	20��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMA5							double	5��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EMA60							double	60��ָ���ƶ����ߣ�Exponential moving average�������ھ��������ӡ�
	EPS								double	����ÿ�����棨Earnings per share��������ÿ��ָ������
	EquityFixedAssetRatio			double	�ɶ�Ȩ����̶��ʲ����ʣ�Equity fixed assets ratio�������㷽�����ɶ�Ȩ����̶��ʲ�����=�ɶ�Ȩ��/(�̶��ʲ�+��������+�ڽ�����)�����ڳ�ծ�������ʱ��ṹ�����ӡ�
	EquityToAsset					double	�ɶ�Ȩ����ʣ�Equity to total assets�������㷽�����ɶ�Ȩ�����=�ɶ�Ȩ��/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	EquityTRate						double	�����������ɶ�Ȩ����ת�ʣ�Equity turnover rate�� ���㷽ʽ���ɶ�Ȩ����ת��=Ӫҵ����/�ɶ�Ȩ��
	ETOP							double	������ֵ�ȣ�Earnings to price�������㷽����������ֵ��=������TTM��/����ֵ������ӯ���������������������ӡ�
	ETP5							double	5��ƽ��������ֵ�ȣ�Five-year average earnings to price�������㷽����5��ƽ��������ֵ��=�����꾻����TTM��/����������ֵ������ӯ���������������������ӡ�
	FinancialExpenseRate			double	���������Ӫҵ������֮�ȣ�Financial expense rate�������㷽�������������Ӫҵ������֮��=������ã�TTM��/Ӫҵ�����루TTM��������ӯ���������������������ӡ�
	FinancingCashGrowRate			double	���ʻ�������ֽ��������������ʡ����㷽�������ʻ�������ֽ���������������=(������ʻ�������ֽ��������TTM��/ȥ����ʻ�������ֽ��������TTM��)-1�������ֽ���ָ�����ӡ�
	FixAssetRatio					double	�̶��ʲ����ʣ�Fixed assets ratio�������㷽�����̶��ʲ�����=(�̶��ʲ�+��������+�ڽ�����)/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	FixedAssetsTRate				double	�̶��ʲ���ת�ʣ�Fixed assets turnover rate�������㷽�����̶��ʲ���ת��=Ӫҵ���루TTM��/�̶��ʲ�+��������+�ڽ����̡�����Ӫ�����������ӡ�
	GrossIncomeRatio				double	����ë���ʣ�Gross income ratio�������㷽��������ë����=(Ӫҵ���루TTM��-Ӫҵ�ɱ���TTM��)/Ӫҵ���루TTM��������ӯ���������������������ӡ�
	HBETA							double	��ʷ������Historical daily beta��������12�����У���������������г����������������Իع飬�г�����������ϵ�������ڳ����������ӡ�
	HSIGMA							double	��ʷ������Historical daily sigma��������12�����У���������������г����������������Իع飬�г����������Ĳв��׼����ڳ����������ӡ�
	IntangibleAssetRatio			double	�����ʲ����ʣ�Intangible assets ratio�������㷽���������ʲ�����=(�����ʲ�+�з�֧��+����)/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	InventoryTDays					double	�����ת������Inventory turnover days�������㷽���������ת����=360/�����ת�ʡ�����Ӫ�����������ӡ�
	InventoryTRate					double	�����ת�ʣ�Inventory turnover rate�������㷽���������ת��=Ӫҵ�ɱ���TTM��/���������Ӫ�����������ӡ�
	InvestCashGrowRate				double	Ͷ�ʻ�������ֽ��������������ʣ�Growth rate of cash flows from investments�������㷽����Ͷ�ʻ�������ֽ���������������=(����Ͷ�ʻ�������ֽ��������TTM��/ȥ��Ͷ�ʻ�������ֽ��������TTM��)-1�������ֽ���ָ�����ӡ�
	LCAP							double	������ֵ��Natural logarithm of total market values�������㷽����������ֵ=��ֵ�Ķ��������ڹ�ֵ����ֵ�����ӡ�
	LFLO							double	������ͨ��ֵ��Natural logarithm of float market values�������㷽����������ͨ��ֵ=��ͨ��ֵ�Ķ��������ڹ�ֵ����ֵ�����ӡ�
	LongDebtToAsset					double	���ڽ�����ʲ��ܼ�֮�ȣ�Long term loan to total assets�������㷽�������ڽ�����ʲ��ܼ�֮��=���ڽ��/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	LongDebtToWorkingCapital		double	���ڸ�ծ��Ӫ���ʽ���ʣ�Long term debt to working capital�������㷽�������ڸ�ծ��Ӫ���ʽ����=��������ծ�ϼ�/(�����ʲ��ϼ�-������ծ�ϼ�)�����ڳ�ծ�������ʱ��ṹ�����ӡ�
	LongTermDebtToAsset				double	���ڸ�ծ���ʲ��ܼ�֮�ȣ�Long term debt to total assets�������㷽�������ڸ�ծ���ʲ��ܼ�֮��=��������ծ�ϼ�/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	MA10							double	10���ƶ����ߣ�Moving average����ȡ���N���ǰ��Ȩ�۸�ľ�ֵ�����ھ��������ӡ�
	MA120							double	120���ƶ����ߣ�Moving average����ȡ���N���ǰ��Ȩ�۸�ľ�ֵ�� ���ھ��������ӡ�
	MA20							double	20���ƶ����ߣ�Moving average����ȡ���N���ǰ��Ȩ�۸�ľ�ֵ�����ھ��������ӡ�
	MA5								double	5���ƶ����ߣ�Moving average����ȡ���N���ǰ��Ȩ�۸�ľ�ֵ�����ھ��������ӡ�
	MA60							double	60���ƶ����ߣ�Moving average����ȡ���N���ǰ��Ȩ�۸�ľ�ֵ�����ھ��������ӡ�
	MAWVAD							double	����WVAD��6�վ�ֵ�����ڳ����������ӡ�
	MFI								double	�ʽ�����ָ�꣨Money Flow Index������ָ����ͨ����ӳ�ɼ۱䶯���ĸ�Ԫ�أ����ǵ��������µ����������ɽ������ӷ��ȡ��ɽ������ٷ������������ܵ����ƣ�Ԥ���г������ϵ���������������ڳ����������ӡ�
	MLEV							double	�г��ܸˣ�Market leverage�������㷽�����г��ܸ�=��������ծ�ϼ�/(��������ծ�ϼ�+����ֵ)�����ڳ�ծ�������ʱ��ṹ�����ӡ�
	NetAssetGrowRate				double	���ʲ������ʣ�Net assets growth rate�������㷽�������ʲ�������=(����ɶ�Ȩ��/ȥ��ɶ�Ȩ��)-1�����ڳɳ����������ӡ�
	NetProfitGrowRate				double	�����������ʣ�Net profit growth rate�������㷽����������������=(���꾻����TTM��/ȥ�꾻����TTM��)-1�����ڳɳ����������ӡ�
	NetProfitRatio					double	���۾����ʣ�Net profit ratio�������㷽�������۾�����=������TTM��/Ӫҵ���루TTM��������ӯ���������������������ӡ�
	NOCFToOperatingNI				double	��Ӫ��������ֽ����������뾭Ӫ�������֮�ȡ����㷽������Ӫ��������ֽ����������뾭Ӫ�������֮��=��Ӫ��������ֽ��������TTM��/(Ӫҵ�����루TTM��-Ӫҵ�ܳɱ���TTM��)�������ֽ���ָ�����ӡ�
	NonCurrentAssetsRatio			double	�������ʲ����ʣ�Non-current assets ratio�������㷽�����������ʲ�����=�������ʲ��ϼ�/���ʲ������ڳ�ծ�������ʱ��ṹ�����ӡ�
	NPParentCompanyGrowRate			double	����ĸ��˾�ɶ��ľ����������ʡ����㷽��������ĸ��˾�ɶ��ľ�����������=(���������ĸ��˾�����ߵľ�����TTM��/ȥ�������ĸ��˾�����ߵľ�����TTM��)-1�����ڳɳ����������ӡ�
	NPToTOR							double	��������Ӫҵ������֮�ȣ�Net profit to total operating revenues�������㷽������������Ӫҵ������֮��=������TTM��/Ӫҵ�����루TTM��������ӯ���������������������ӡ�
	OperatingExpenseRate			double	Ӫҵ������Ӫҵ������֮�ȣ�Operating expense rate�������㷽����Ӫҵ������Ӫҵ������֮��=���۷��ã�TTM��/Ӫҵ�����루TTM��������ӯ���������������������ӡ�
	OperatingProfitGrowRate			double	Ӫҵ���������ʣ�Operating profit growth rate�������㷽����Ӫҵ����������=(����Ӫҵ����TTM��/ȥ��Ӫҵ����TTM��)-1�����ڳɳ����������ӡ�
	OperatingProfitRatio			double	Ӫҵ�����ʣ�Operating profit ratio�������㷽����Ӫҵ������=Ӫҵ����TTM��/Ӫҵ���루TTM��������ӯ���������������������ӡ�
	OperatingProfitToTOR			double	Ӫҵ������Ӫҵ������֮�ȣ�Operating profit to total operating revenues�������㷽����Ӫҵ������Ӫҵ������֮��=Ӫҵ����TTM��/Ӫҵ�����루TTM��������ӯ���������������������ӡ�
	OperatingRevenueGrowRate		double	Ӫҵ���������ʣ�Operating revenue growth rate�������㷽����Ӫҵ����������=������Ӫҵ���루TTM��/ȥ��Ӫҵ���루TTM����-1�����ڳɳ����������ӡ�
	OperCashGrowRate				double	��Ӫ��������ֽ��������������ʡ����㷽������Ӫ��������ֽ���������������=(���꾭Ӫ��������ֽ��������TTM��/ȥ�꾭Ӫ��������ֽ��������TTM��)-1�������ֽ���ָ�����ӡ�
	OperCashInToCurrentLiability	double	�ֽ�������ծ�ȣ�Cash provided by operations to current liability�������㷽�����ֽ�������ծ��=��Ӫ��������ֽ��������TTM��/������ծ�ϼơ������ֽ���ָ�����ӡ�
	PB								double	�о��ʣ�Price-to-book ratio�������㷽�����о���=����ֵ/������ĸ��˾������Ȩ��ϼơ����ڹ�ֵ����ֵ�����ӡ�
	PCF								double	�����ʣ�Price-to-cash-flow ratio�������㷽��������ֵ/��Ӫ��������ֽ��������TTM�������ڹ�ֵ����ֵ�����ӡ�
	PE								double	��ӯ�ʣ�Price-earnings ratio����ʹ��TTM�㷨����ӯ��=����ֵ/������ĸ��˾�����ߵľ�����TTM�������ڹ�ֵ����ֵ�����ӡ�
	PS								double	�����ʣ�Price-to-sales ratio����������=����ֵ/Ӫҵ�����루TTM�������ڹ�ֵ����ֵ�����ӡ�
	PSY								double	������ָ�꣨Psychological line index������һ��ʱ����Ͷ���������򷽻�������������ʵת����ֵ�����������жϹɼ۵�δ�����ơ��������������ӡ�
	QuickRatio						double	�ٶ����ʣ�Quick ratio�������㷽�����ٶ�����=(�����ʲ��ϼ�-���)/ ������ծ�ϼơ����ڳ�ծ�������ʱ��ṹ�����ӡ�
	REVS10							double	��Ʊ��10�����档���ڳ����������ӡ�
	REVS20							double	��Ʊ��20�����档���ڳ����������ӡ�
	REVS5							double	��Ʊ��5�����档���ڳ����������ӡ�
	ROA								double	�ʲ��ر��ʣ�Return on assets�������㷽�����ʲ��ر���=������TTM��/���ʲ�������ӯ���������������������ӡ�
	ROA5							double	5���ʲ��ر��ʣ�Five-year average return on assets�������㷽����5���ʲ��ر���=������TTM��/���ʲ�������ӯ���������������������ӡ�
	ROE								double	Ȩ��ر��ʣ�Return on equity�������㷽����Ȩ��ر���=������TTM��/�ɶ�Ȩ�档����ӯ���������������������ӡ�
	ROE5							double	����������5 ��Ȩ��ر��ʣ�Five-year average return on equity�� ���㷽ʽ��5 ��Ȩ��ر���=������/�ɶ�Ȩ��
	RSI								double	���ǿ��ָ�꣨Relative Strength Index����ͨ���Ƚ�һ��ʱ���ڵ�ƽ������������ƽ�����̵����������г�����̵������ʵ�����ݴ�Ԥ�����Ƶĳ�������ת�����ڳ����������ӡ�
	RSTR12							double	12�����ǿ�ƣ�Relative strength for the last 12 months�����������������ӡ�
	RSTR24							double	12�����ǿ�ƣ�Relative strength for the last 24 months�����������������ӡ�
	SalesCostRatio					double	���۳ɱ��ʣ�Sales cost ratio�������㷽�������۳ɱ���=Ӫҵ�ɱ���TTM��/Ӫҵ���루TTM��������ӯ���������������������ӡ�
	SaleServiceCashToOR				double	������Ʒ�ṩ�����յ����ֽ���Ӫҵ����֮�ȣ�Sale service cash to operating revenues�������㷽����������Ʒ�ṩ�����յ����ֽ���Ӫҵ����֮��=������Ʒ���ṩ�����յ����ֽ�TTM��/Ӫҵ���루TTM���������ֽ���ָ�����ӡ�
	SUE								double	δԤ��ӯ�ࣨStandardized unexpected earnings�������㷽����δԤ��ӯ��=(���һ�꾻����-��ȥ���һ��Ĺ����������ֵ)/ ��ȥ���һ��Ĺ����������׼�����ӯ���������������������ӡ�
	TaxRatio						double	����˰���ʣ�Tax ratio�������㷽��������˰����=Ӫҵ˰�𼰸��ӣ�TTM��/Ӫҵ���루TTM��������ӯ���������������������ӡ�
	TOBT							double	����������Liquidity-turnover beta�����������������ӡ�
	TotalAssetGrowRate				double	���ʲ������ʣ�Total assets growth rate�������㷽�������ʲ�������=(�������ʲ�/ȥ�����ʲ�)-1�����ڳɳ����������ӡ�
	TotalAssetsTRate				double	�������������ʲ���ת�ʣ�Total assets turnover rate�� ���㷽ʽ�����ʲ���ת��=Ӫҵ����/���ʲ�
	TotalProfitCostRatio			double	�ɱ����������ʣ�Total profit cost ratio�������㷽�����ɱ�����������=�����ܶ�/(Ӫҵ�ɱ�+�������+���۷���+�������)�����Ͽ�Ŀʹ�õĶ���TTM����ֵ������ӯ���������������������ӡ�
	TotalProfitGrowRate				double	�����ܶ������ʣ�Total profit growth rate�������㷽���������ܶ�������=(���������ܶTTM��/ȥ�������ܶTTM��)-1�����ڳɳ����������ӡ�
	VOL10							double	10��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	VOL120							double	120��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	VOL20							double	20��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	VOL240							double	240��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	VOL5							double	5��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	VOL60							double	60��ƽ�������ʣ�Turnover Rate�������ڳɽ���������
	WVAD							double	����������ɢ����William's variable accumulation distribution������һ�ֽ��ɽ�����Ȩ������ָ�꣬���ڲ����ӿ��̼������̼��ڼ䣬����˫�����Ա������ĳ̶ȡ����ڳ����������ӡ�
	REC								double	����ʦ�Ƽ�������Recommended rating score by analyst�������ڷ���ʦԤ�������ӡ�
	DAREC							double	����ʦ�Ƽ������仯��Changes of recommended rating score by analyst���������60 ��������ǰ�����ڷ���ʦԤ�������ӡ�
	GREC							double	����ʦ�Ƽ������仯���ƣ�Change tendency of recommended rating score by analyst������ȥ60 ���������ڵ�DAREC ���żӺ͡����ڷ���ʦԤ�������ӡ�
	FY12P							double	����ʦӯ��Ԥ�⣨Forecast earnings by analyst to market values�������ڷ���ʦԤ�������ӡ�
	DAREV							double	����ʦӯ��Ԥ��仯��Changes of forecast earnings by analyst���������60��������ǰ�����ڷ���ʦԤ�������ӡ�
	GREV							double	����ʦӯ��Ԥ��仯���ƣ�Change tendency of forecast earnings by analyst������ȥ60���������ڵ�DAREV���żӺ͡����ڷ���ʦԤ�������ӡ�
	SFY12P							double	����ʦӪ��Ԥ�⣨Forecast sales by analyst to market values�������ڷ���ʦԤ�������ӡ�
	DASREV							double	����ʦӯ��Ԥ��仯��Changes of forecast sales by analyst���������60 ��������ǰ�����ڷ���ʦԤ�������ӡ�
	GSREV							double	����ʦӯ��Ԥ��仯���ƣ�Change tendency of forecast sales by analyst������ȥ60 ���������ڵ�DASREV ���żӺ͡����ڷ���ʦԤ�������ӡ�
	FEARNG							double	δ��Ԥ��ӯ��������Growth of forecast earnings�������ڷ���ʦԤ�������ӡ�
	FSALESG							double	δ��Ԥ��ӯ��������Growth of forecast sales�������ڷ���ʦԤ�������ӡ�
	TA2EV							double	�ʲ��ܼ�����ҵ��ֵ֮�ȣ�Assets to enterprise value�������ڹ�ֵ����ֵ�����ӡ�
	CFO2EV							double	��Ӫ��������ֽ�������������ҵ��ֵ֮�ȣ�Cash provided by operations to enterprise value���������ֽ���ָ�����ӡ�
	ACCA							double	�ֽ����ʲ��Ⱥ��ʲ��ر���֮�Cash flow assets ratio minus return on assets�������㷽�����ֽ����ʲ��Ⱥ��ʲ��ر���֮��=����Ӫ������Ľ��������TTM�� - ������TTM����/ ���ʲ��������ֽ���ָ�����ӡ�
	DEGM							double	ë����������Growth rate of gross income ratio����ȥ��ͬ����ȡ����㷽����ë��������=(����ë���ʣ�TTM��/ȥ��ë���ʣ�TTM��)-1�����ڳɳ����������ӡ�
	SUOI							double	δԤ��ë����Standardized unexpected gross income��������ӯ���������������������ӡ�
	EARNMOM							double	�˼��Ⱦ�����仯���ƣ�Change tendency of net profit in the past eight quarters����ǰ8�����ȵľ��������ͬ�ȣ�ȥ��ͬ�ڣ�������Ϊ+1��ͬ���»���Ϊ-1���ٽ�8 ��ֵ��ӡ����ڳɳ����������ӡ�
	FiftyTwoWeekHigh				double	��ǰ�۸��ڹ�ȥ1 ��ɼ۵�λ�ã�Price level during the pasted 52 weeks�������ڳ����������ӡ�
	Volatility						double	��������Բ����ʣ�Volatility of daily turnover during the last N days�������ڳ����������ӡ�
	Skewness						double	�ɼ�ƫ�ȣ�Skewness of price during the last N days������ȥ20�������չɼ۵�ƫ�ȡ����ڳ����������ӡ�
	ILLIQUIDITY						double	������Խ��ȣ�Daily return to turnover value during the last N days������ȥ20��������������Խ��ı��������ڳ����������ӡ�
	BackwardADJ						double	�ɼ����Ȩ���ӣ���Ȩ�ǶԹɼۺͳɽ�������ȨϢ�޸������ڳ����������ӡ�
	MACD							double	ƽ����ͬ�ƶ�ƽ���ߣ�Moving Average Convergence Divergence��,�ֳ��ƶ�ƽ����ɢָ�ꡣ��������������
	*/
};
//////////////////////////////////////////////////////////////////////////
//����
struct GD_RealTime_Req					//ʵ����������
{
	bool	isAllMarket;				//�Ƿ���ȫ�г�
	int		nBeginTime;					//��ʼ�����ʱ��  0 Ϊ�ӵ�ǰʱ�̣� -1 Ϊ�ӿ��̿�ʼ��hhMMsszzz(903001000) Ϊ��ָ��ʱ�俪ʼ
	int		nSubDataType;				//���Ĵ�������
	int		nCodeNum;					//��������
	GD_CodeType szCodes[1];				//���Ĵ����׵�ַ
};

struct GD_RealTimeGDKline_Req
{
	int		nCycType;					//��������
	bool	isAllMarket;				//�Ƿ���ȫ�г�
	int		nBeginTime;					//��ʼ�����ʱ��  0 Ϊ�ӵ�ǰʱ�̣� -1 Ϊ�ӿ��̿�ʼ��hhMMsszzz(903001000) Ϊ��ָ��ʱ�俪ʼ
	int		nCodeNum;					//��������
	GD_CodeType szCodes[1];				//���Ĵ����׵�ַ
};

struct GD_UpdateSubCodes_Req
{
	GD_UpdateSubCodeType nType;			//��������
	bool	isAllMarket;				//�Ƿ���ȫ�г�
	int		nCodeNum;					//��������
	GD_CodeType szCodes[1];				//���Ĵ����׵�ַ
};

struct GD_SimulationTimeline_Req
{
	GD_ISODateTimeType szBeginDatetime;	//����ʼ��ʱ��
	GD_PlaybackSpeedType nType;			//�ط��ٶ�
};

typedef GD_RealTime_Req GD_SimulationTick_Req;
typedef GD_RealTimeGDKline_Req GD_SimulationGDKline_Req;
typedef GD_UpdateSubCodes_Req GD_SimulationUpdateSubCodes_Req;

struct GD_HistoryData_Req				//ģ����������
{
	GD_ISODateTimeType szBeginDatetime;	//����ʼ��ʱ��
	GD_ISODateTimeType szEndDatetime;	//���������ʱ��
	GD_PlaybackSpeedType nModelType;		//�ز�ģʽ
	bool	isAllMarket;				//�Ƿ���ȫ�г�
	int		nCodeNum;					//��������
	GD_CodeType szCodes[1];				//���Ĵ����׵�ַ
};

struct GD_HistoryKline_Req						//ģ����������
{
	GD_CycType nType;					//��������
	GD_ISODateTimeType szBeginDatetime;	//����ʼ��ʱ��
	GD_ISODateTimeType szEndDatetime;	//���������ʱ��
	bool	isAllMarket;				//�Ƿ���ȫ�г�
	int		nCodeNum;					//��������
	GD_CodeType szCodes[1];				//���Ĵ����׵�ַ
};

struct GD_TradingDay_Req				//��ѯһ��ʱ���ڵ����н�����
{
	GD_ISODateTimeType szBeginDay;		//��ʼʱ��
	GD_ISODateTimeType szEndDay;		//������ʱ��
};

//////////////////////////////////////////////////////////////////////////
//�ص�

typedef GD_ISODateTimeType GD_TradingDateBegin_Rsp;		//�����տ�ʼ
typedef GD_ISODateTimeType GD_TradingDateEnd_Rsp;		//�����ս���
typedef GD_SimulationTimeline_Req GD_SimulationTimelineConfirmed_Rsp;	//ģ��ʱ����ȷ�ϣ���ʼ�ط�����

//�������������ʹ���
typedef char PT_ServerTypeCD;
const PT_ServerTypeCD		Realtime_PT_ServerTypeCD = 10;		//ʵʱ���������
const PT_ServerTypeCD		History_PT_ServerTypeCD = 12;		//��ʷ���������

struct GD_Kline_Data						//ģ����������
{
	GD_CycType nType;					//��������
	char	szCode[32];					//�Ƿ���ȫ�г�
	GD_ISODateTimeType szDatetime;		//ʱ��
	unsigned int nDate;					//���� yyyyMMdd
	unsigned int nTime;					//ʱ�� hhmmsszzz
	double	nOpen;
	double	nHigh;
	double	nLow;
	double	nClose;
	double	nPreClose;					//�������̼�
	double	nHighLimit;
	double	nLowLimit;
	unsigned long long iVolume;
	double	nTurover;
};

struct GD_Stock_Timeliness_Notification
{
	bool isTick;						//True Ϊtick, false ΪK������
	GD_TimelinessType nType;			//����ʱЧ������
	GD_CodeType szCode;					//��������
};

struct GD_TradingDay_Rsp
{
	unsigned nNum;
	GD_ISODateTimeType mDayList[1];		//�������б��׵�ַ
};

//ָ��
struct GD_MA_Setting
{
	
};

struct GD_MA
{
	GD_CodeType szCode;					//����
	GD_ISODateTimeType szDatetime;		//ʱ��
	GD_CycType nCycType;				//��������

	double nMA1;
	double nMA2;
	double nMA3;
};

#pragma pack(pop)
#endif // GETDATASTRUCT_H
