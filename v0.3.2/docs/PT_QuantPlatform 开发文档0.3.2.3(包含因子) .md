 ![logo](C:\Users\Administrator\Desktop\logo.png)                                                         子午投资 PT_QuantPlatform开发文档

------



# 子午投资

# PT_QuantPlatform开发文档

|          |               |          |                    |
| -------- | ------------- | -------- | ------------------ |
| **研制单位** | 子午投资管理有限公司    | **应用单位** |                    |
| **项目名称** |               | **项目编号** |                    |
| **文档名称** | PT_QuantPform | **文档编号** |                    |
| **文档状态** | 草稿            | **文档版本** | 1.0.0.1013.release |
| **提交**   |               | **提交日期** | 2016年10月13日        |
| **审批**   |               | **审批日期** |                    |
|          |               |          |                    |

------

​                                                                          **修改记录**

| 文档版本               | 文档状态    | 修订日期       | 修订者  | 修订内容    |
| ------------------ | ------- | ---------- | ---- | ------- |
| 1.0.0.1012.release | Created | 2016-10-12 | 王商   |         |
| 1.0.0.1013.release | Added   | 2016-10-13 | 王商   | 添加各参数说明 |
|                    |         |            |      |         |
|                    |         |            |      |         |
|                    |         |            |      |         |
|                    |         |            |      |         |
|                    |         |            |      |         |
|                    |         |            |      |         |

文档状态标识：Created-Added-Modified-Deleted







[TOC]

# 1 行情接口

## 1.1 系统构架

暂略

## 1.2 开发包文件结构

暂略

## 1.3 访问回调时序图

暂略

## 1.4创建回调函数实例

```c++
class MarketClient : public GetDataSpi
{
private:
	GD_ErrorType m_err;
	PT_QuantPlatform::GetDataApi* m_api;
	vector<TDF_CODE*> m_allCode;
	TradeClient* m_tclient;
public:
//	void stressTesting();
public:
	virtual void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum)
	{
		cout << codeNum << endl;
	};		//代码表

	virtual void OnRecvMarket(TDF_MARKET_DATA* pMarket){};     								//行情
	virtual void OnRecvFuture(TDF_FUTURE_DATA* pFuture){};									//期货
	virtual void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture){};							//期权
	virtual void OnRecvIndex(TDF_INDEX_DATA* pIndex){};										//指数
	virtual void OnRecvTransaction(TDF_TRANSACTION* pTransaction){};							//逐笔
	virtual void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue){};							//委托队列
	virtual void OnRecvOrder(TDF_ORDER* pOrder){};											//逐笔委托数据（仅深市有）
	virtual void OnRecvGDKLine(GD_Kline_Data* pKline){};									//K线数据

	virtual void OnRecvDayBegin(GD_ISODateTimeType pDate)
	{
		cout << "DayBegin:" << endl;
	};			//接收当前交易日
	virtual void OnRecvDayEnd(GD_ISODateTimeType pDate)
	{
		cout << "DayEnd:" << endl;
	};				//接收到闭市消息

	//每次数据日期变更都会通知这两个接口，无论是历史还是实时
	virtual void OnRecvRspOver(){}

	//系统信息
	virtual void OnConnect(){};
	virtual void OnDisconnect(){};
	virtual void OnReconnectStatus(bool successed){};

	virtual void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData){};		//数据时效性状态切换通知，通过这个
	virtual void OnError(string error){};	//错误信息


public:
	MarketClient(TradeClient* tClient){};
	~MarketClient(){};
};
```

## 1.5 获取行情连接对象实例

```c++
API_EXPORT PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, PT_QuantPlatform::TradeDataApi* tApi = NULL, bool enableLog = true);
```

| 参数           | 类型                              | 说明                                       |
| ------------ | ------------------------------- | ---------------------------------------- |
| spi          | PT_QuantPlatform::GetDataSpi*   | 自定义的回调类的实例对象指针                           |
| autoRecon    | bool                            | 是否断线后自动连接                                |
| reconTimeOut | int                             | 断线重连重试时间间隔，单位毫秒                          |
| autoReq      | bool                            | 用标识自动重连后，是否自动发送上一个请求；默认值为*false*。        |
| tApi         | PT_QuantPlatform::TradeDataApi* | 交易对象实例指针，在使用模拟引擎撮合时，必须把交易对象实例指针传进来，否则将没有行情进行撮合处理；默认值为*NULL*。 |
| enableLog    | bool                            | 是否开启日志功能；默认值为*true*。                     |
|              |                                 |                                          |

## 1.6 释放行情连接对象实例

```c++
API_EXPORT void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
```

| 参数   | 类型                            | 说明            |
| ---- | ----------------------------- | ------------- |
| pAPI | PT_QuantPlatform::GetDataApi* | 需要释放的行情对象实例指针 |
|      |                               |               |

## 1.7 行情Spi参数说明



### 1.7.1 代码表获取

登录成功后即会马上调用该回调。

```c++
void OnRecvCode(TDF_CODE* pCode, int codeNum, TDF_OPTION_CODE* pOptionCode, int optionCodeNum)；
```

| 参数            | 类型               | 说明   |
| ------------- | ---------------- | ---- |
| pCode         | TDF_CODE*        | 股票代码 |
| codeNum       | int              | 股票数量 |
| pOptionCode   | TDF_OPTION_CODE* | 期权代码 |
| optionCodeNum | int              | 期权数量 |
|               |                  |      |

TDF_CODE 各项参数说明：

| 参数名称       | 参数类型     | 说明                    |
| ---------- | -------- | --------------------- |
| szWindCode | char[32] | Wind Code: AG1302.SHF |
| szMarket   | char[8]  | market code: SHF      |
| szCode     | char[32] | original code:ag1302  |
| szENName   | char[32] |                       |
| szCNName   | char[32] | chinese name: 沪银1302  |
| nType      | int      |                       |
|            |          |                       |

TDF_OPTION_CODE 各项参数说明：

| 参数名称                    | 参数类型     | 说明                                       |
| ----------------------- | -------- | ---------------------------------------- |
| basicCode               | TDF_CODE | 股票代码                                     |
| szContractID            | char[32] | 期权合约代码                                   |
| szUnderlyingSecurityID  | char[32] | 标的证券代码                                   |
| chCallOrPut             | char     | 认购认沽C1;认购，则本字段为“C”；若为认沽，则本字段为“P”。        |
| nExerciseDate           | int      | 期权行权日，YYYYMMDD                           |
| chUnderlyingType        | char     | 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)。 |
| chOptionType            | char     | 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”。 |
| chPriceLimitType        | char     | 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型，‘R’表示无涨跌幅限制类型。   |
| nContractMultiplierUnit | int      | 合约单位，经过除权除息调整后的合约单位， 一定是整数。              |
| nExercisePrice          | int      | 期权行权价，经过除权除息调整后的期权行权价，右对齐，精确到厘。          |
| nStartDate              | int      | 期权首个交易日，YYYYMMDD。                        |
| nEndDate                | int      | 期权最后交易日/行权日，YYYYMMDD。                    |
| nExpireDate             | int      | 期权到期日，YYYYMMDD。                          |
|                         |          |                                          |

### 1.7.2 行情

```c++
void OnRecvMarket(TDF_MARKET_DATA* pMarket);
```

| 参数      | 类型               | 说明     |
| ------- | ---------------- | ------ |
| pMarket | TDF_MARKET_DATA* | 行情快照数据 |
|         |                  |        |

TDF_MARKET_DATA 各项参数说明：

| 参数名称                 | 参数类型             | 说明            |
| -------------------- | ---------------- | ------------- |
| szWindCode           | char[32]         | 600001.SH     |
| szCode               | char[32]         | 原始Code        |
| nActionDay           | int              | 业务发生日(自然日)    |
| nTradingDay          | int              | 交易日           |
| nTime                | int              | 时间(HHMMSSmmm) |
| nStatus              | int              | 状态            |
| nPreClose            | unsigned int     | 前收盘价          |
| nOpen                | unsigned int     | 开盘价           |
| nHigh                | unsigned int     | 最高价           |
| nLow                 | unsigned int     | 最低价           |
| nMatch               | unsigned int     | 最新价           |
| nAskPrice            | unsigned int[10] | 申卖价           |
| nAskVol              | unsigned int[10] | 申卖量           |
| nBidPrice            | unsigned int[10] | 申买价           |
| nBidVol              | unsigned int[10] | 申买量           |
| nNumTrades           | unsigned int     | 成交笔数          |
| iVolume              | __int64          | 成交总量          |
| iTurnover            | __int64          | 成交总金额         |
| nTotalBidVol         | __int64          | 委托买入量         |
| nTotalAskVol         | __int64          | 委托卖出量         |
| nWeightedAvgBidPrice | unsigned int     | 加权平均委买价格      |
| nWeightedAvgAskPrice | unsigned int     | 加权平均委卖价格      |
| nIOPV                | int              | IOPV净值估值      |
| nYieldToMaturity     | int              | 到期收益率         |
| nHighLimited         | unsigned int     | 涨停价           |
| nLowLimited          | unsigned int     | 跌停价           |
| chPrefix             | char[4]          | 证券信息前缀        |
| nSyl1                | int              | 市盈率1          |
| nSyl2                | int              | 市盈率2          |
| nSD2                 | int              | 升跌2（对比上一笔）    |
|                      |                  |               |

### 1.7.3 期货

```c++
void OnRecvFuture(TDF_FUTURE_DATA* pFuture);
```

| 参数      | 类型               | 说明   |
| ------- | ---------------- | ---- |
| pFuture | TDF_FUTURE_DATA* | 期货数据 |
|         |                  |      |

TDF_FUTURE_DATA 各项参数说明：

| 参数名称             | 参数类型            | 说明             |
| ---------------- | --------------- | -------------- |
| szWindCode       | char[32]        | 600001.SH      |
| szCode           | char[32]        | 原始Code         |
| nActionDay       | int             | 业务发生日(自然日)     |
| nTradingDay      | int             | 交易日            |
| nTime            | int             | 时间(HHMMSSmmm)  |
| nStatus          | int             | 状态             |
| iPreOpenInterest | __int64         | 昨持仓            |
| nPreClose        | unsigned int    | 昨收盘价           |
| nPreSettlePrice  | unsigned int    | 昨结算            |
| nOpen            | unsigned int    | 开盘价            |
| nHigh            | unsigned int    | 最高价            |
| nLow             | unsigned int    | 最低价            |
| nMatch           | unsigned int    | 最新价            |
| iVolume          | __int64         | 成交总量           |
| iTurnover        | __int64         | 成交总金额          |
| iOpenInterest    | __int64         | 持仓总量           |
| nClose           | unsigned int    | 今收盘            |
| nSettlePrice     | unsigned int    | 今结算            |
| nHighLimited     | unsigned int    | 涨停价            |
| nLowLimited      | unsigned int    | 跌停价            |
| nPreDelta        | int             | 昨虚实读           |
| nCurrDelta       | int             | 今虚实度           |
| nAskPrice        | unsigned int[5] | 申卖价            |
| nAskVol          | unsigned int[5] | 申卖量            |
| nBidPrice        | unsigned int[5] | 申买价            |
| nBidVol          | unsigned int[5] | 申买量            |
| lAuctionPrice    | int             | 波动性中断参考价       |
| lAuctionQty      | int             | 波动性中断集合竞价虚拟匹配量 |
|                  |                 |                |

### 1.7.4 期权

```c++
void OnRecvFutureOption(TDF_FUTURE_DATA* pFuture);
```

| 参数      | 类型               | 说明   |
| ------- | ---------------- | ---- |
| pFuture | TDF_FUTURE_DATA* | 期权数据 |
|         |                  |      |

TDF_FUTURE_DATA 各项参数说明：

| 参数名称             | 参数类型            | 说明             |
| ---------------- | --------------- | -------------- |
| szWindCode       | char[32]        | 600001.SH      |
| szCode           | char[32]        | 原始Code         |
| nActionDay       | int             | 业务发生日(自然日)     |
| nTradingDay      | int             | 交易日            |
| nTime            | int             | 时间(HHMMSSmmm)  |
| nStatus          | int             | 状态             |
| iPreOpenInterest | __int64         | 昨持仓            |
| nPreClose        | unsigned int    | 昨收盘价           |
| nPreSettlePrice  | unsigned int    | 昨结算            |
| nOpen            | unsigned int    | 开盘价            |
| nHigh            | unsigned int    | 最高价            |
| nLow             | unsigned int    | 最低价            |
| nMatch           | unsigned int    | 最新价            |
| iVolume          | __int64         | 成交总量           |
| iTurnover        | __int64         | 成交总金额          |
| iOpenInterest    | __int64         | 持仓总量           |
| nClose           | unsigned int    | 今收盘            |
| nSettlePrice     | unsigned int    | 今结算            |
| nHighLimited     | unsigned int    | 涨停价            |
| nLowLimited      | unsigned int    | 跌停价            |
| nPreDelta        | int             | 昨虚实读           |
| nCurrDelta       | int             | 今虚实度           |
| nAskPrice        | unsigned int[5] | 申卖价            |
| nAskVol          | unsigned int[5] | 申卖量            |
| nBidPrice        | unsigned int[5] | 申买价            |
| nBidVol          | unsigned int[5] | 申买量            |
| lAuctionPrice    | int             | 波动性中断参考价       |
| lAuctionQty      | int             | 波动性中断集合竞价虚拟匹配量 |
|                  |                 |                |

### 1.7.5 指数

```c++
void OnRecvIndex(TDF_INDEX_DATA* pIndex);
```

| 参数     | 类型              | 说明   |
| ------ | --------------- | ---- |
| pIndex | TDF_INDEX_DATA* | 指数数据 |
|        |                 |      |

TDF_INDEX_DATA 各项参数说明：

| 参数名称           | 参数类型     | 说明            |
| -------------- | -------- | ------------- |
| szWindCode     | char[32] | 600001.SH     |
| szCode         | char[32] | 原始Code        |
| nActionDay     | int      | 业务发生日(自然日)    |
| nTradingDay    | int      | 交易日           |
| nTime          | int      | 时间(HHMMSSmmm) |
| nOpenIndex     | int      | 今开盘指数         |
| nHighIndex     | int      | 最高指数          |
| nLowIndex      | int      | 最低指数          |
| nLastIndex     | int      | 最新指数          |
| iTotalVolume   | __int64  | 参与计算相应指数的交易数量 |
| iTurnover      | __int64  | 参与计算相应指数的成交金额 |
| nPreCloseIndex | int      | 前盘指数          |
|                |          |               |

### 1.7.6 逐笔

```c++
void OnRecvTransaction(TDF_TRANSACTION* pTransaction);
```

| 参数           | 类型               | 说明     |
| ------------ | ---------------- | ------ |
| pTransaction | TDF_TRANSACTION* | 逐笔成交数据 |
|              |                  |        |

TDF_TRANSACTION 各项参数说明：

| 参数名称           | 参数类型     | 说明                         |
| -------------- | -------- | -------------------------- |
| szWindCode     | char[32] | 600001.SH                  |
| szCode         | char[32] | 原始Code                     |
| nActionDay     | int      | 自然日                        |
| nTime          | int      | 成交时间(HHMMSSmmm)            |
| nIndex         | int      | 成交编号                       |
| nPrice         | int      | 成交价格                       |
| nVolume        | int      | 成交数量                       |
| nTurnover      | int      | 成交金额                       |
| nBSFlag        | int      | 买卖方向(买：'B', 卖：'A', 不明：' ') |
| chOrderKind    | char     | 成交类别                       |
| chFunctionCode | char     | 成交代码                       |
| nAskOrder      | int      | 叫卖方委托序号                    |
| nBidOrder      | int      | 叫买方委托序号                    |
|                |          |                            |

### 1.7.7 委托队列

```c++
 void OnRecvOrderQueue(TDF_ORDER_QUEUE* pOrderQueue);
```

| 参数          | 类型               | 说明     |
| ----------- | ---------------- | ------ |
| pOrderQueue | TDF_ORDER_QUEUE* | 委托队列数据 |
|             |                  |        |

TDF_ORDER_QUEUE 各项参数说明：

| 参数名称       | 参数类型     | 说明                    |
| ---------- | -------- | --------------------- |
| szWindCode | char[32] | 600001.SH             |
| szCode     | char[32] | 原始Code                |
| nActionDay | int      | 自然日                   |
| nTime      | int      | 时间(HHMMSSmmm)         |
| nSide      | int      | 买卖方向('B':Bid 'A':Ask) |
| nPrice     | int      | 委托价格                  |
| nOrders    | int      | 订单数量                  |
| nABItems   | int      | 明细个数                  |
| nABVolume  | int[200] | 订单明细                  |
|            |          |                       |

### 1.7.8 逐笔委托数据

注：仅深市有

```c++
void OnRecvOrder(TDF_ORDER* pOrder);
```

| 参数     | 类型         | 说明           |
| ------ | ---------- | ------------ |
| pOrder | TDF_ORDER* | 逐笔委托数据（仅深市有） |
|        |            |              |

TDF_ORDER 各项参数说明：

| 参数名称           | 参数类型     | 说明                |
| -------------- | -------- | ----------------- |
| szWindCode     | char[32] | 600001.SH         |
| szCode         | char[32] | 原始Code            |
| nActionDay     | int      | 委托日期(YYMMDD)      |
| nTime          | int      | 委托时间(HHMMSSmmm)   |
| nOrder         | int      | 委托号               |
| nPrice         | int      | 委托价格              |
| nVolume        | int      | 委托数量              |
| chOrderKind    | char     | 委托类别              |
| chFunctionCode | char     | 委托代码('B','S','C') |
|                |          |                   |

### 1.7.9 k线数据

```c++
void OnRecvGDKLine(GD_Kline_Data* pKline);
```

| 参数                                 | 类型             | 说明   |
| ---------------------------------- | -------------- | ---- |
| pKline                             | GD_Kline_Data* | k线数据 |
| GD_SimulationTimelineConfirmed_Rsp |                |      |

GD_Kline_Data 各项参数说明：

| 参数名称       | 参数类型               | 说明                              |
| ---------- | ------------------ | ------------------------------- |
| nType      | GD_CycType         | 周期类型(注：见**数据字典1**)              |
| szCode     | char[32]           | 是否订阅全市场                         |
| szDatetime | char[21]           | 日期和时间类型(格式 yyyy-MM-dd hh:mm:ss) |
| nDate      | unsigned int       | 日期：yyyyMMdd                     |
| nTime      | unsigned int       | 时间：hhmmsszzz                    |
| nOpen      | double             |                                 |
| nHigh      | double             |                                 |
| nLow       | double             |                                 |
| nClose     | double             |                                 |
| nPreClose  | double             | 昨日收盘价                           |
| nHighLimit | double             |                                 |
| nLowLimit  | double             |                                 |
| iVolume    | unsigned long long |                                 |
| nTurover   | double             |                                 |
|            |                    |                                 |

### 1.7.10 模拟时间线确认回调

每次数据日期变更都会通知这两个接口，无论是历史还是实时。

```c++
void OnRecvRspSimulationTimelineConfirmed(GD_SimulationTimelineConfirmed_Rsp* pConfirmed);
```

| 参数         | 类型                                  | 说明        |
| ---------- | ----------------------------------- | --------- |
| pConfirmed | GD_SimulationTimelineConfirmed_Rsp* | 模拟时间线确认回调 |
|            |                                     |           |

### 1.7.11 接收当前交易日

```c++
void OnRecvDayBegin(GD_ISODateTimeType pDate);
```

| 参数    | 类型                 | 说明                               |
| ----- | ------------------ | -------------------------------- |
| pDate | GD_ISODateTimeType | 当前交易日时间点(格式 yyyy-MM-dd hh:mm:ss) |
|       |                    |                                  |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |

### 1.7.12 接收到闭市消息

```c++
void OnRecvDayEnd(GD_ISODateTimeType pDate);
```

| 参数    | 类型                 | 说明                               |
| ----- | ------------------ | -------------------------------- |
| pDate | GD_ISODateTimeType | 当前交易日时间点(格式 yyyy-MM-dd hh:mm:ss) |
|       |                    |                                  |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
| char[21]           |          |      |

### 1.7.13 数据接受完毕

每次历史数据请求结束都会调用这个接口

```c++
void OnRecvRspOver();
```

### 1.7.14 交易日查询回调

```c++
void OnRspTradingDay(GD_ISODateTimeType* pDay, int dayNum);
```

| 参数     | 类型                 | 说明        |
| ------ | ------------------ | --------- |
| pDay   | GD_ISODateTimeType | 接收当前交易日消息 |
| dayNum | int                | 交易日列表     |
|        |                    |           |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |

### 1.7.15 前复权因子

```c++
void OnRevRestorationFactor(GD_RestorationFactor* factor, int factorNum);
```

| 参数        | 类型                    | 说明     |
| --------- | --------------------- | ------ |
| factor    | GD_RestorationFactor* | 前复权因子  |
| factorNum | int                   | 复权因子列表 |
|           |                       |        |

GD_RestorationFactor 各项参数说明：

| 参数名称                    | 参数类型               | 说明         |
| ----------------------- | ------------------ | ---------- |
| szWindCode              | GD_CodeType        | 证券代码       |
| szExDivDate             | GD_ISODateTimeType | 除息除权日      |
| nPerCashDiv             | double             | 每股派现       |
| nPerShareDivRatio       | double             | 每股送股比例     |
| nPerShareTransRatio     | double             | 每股转增股比例    |
| nAllotmentRatio         | double             | 每股配股比例     |
| nAllotmentPrice         | double             | 配股价        |
| nRestorationFactor      | double             | 复权因子(前复权)  |
| nAccumRestorationFactor | double             | 累积复权因子     |
| szEndDate               | char[21]           | 累积复权因子截止日期 |
|                         |                    |            |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_CodeType        | char[32] |      |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |

### 1.7.16 连接成功系统通知

```c++
void OnConnect();
```



### 1.7.17 断线系统通知

```c++
void OnDisconnect();
```



### 1.7.18 自动断线重连状态通知

是否连接成功。

```c++
void OnReconnectStatus(bool successed);
```



### 1.7.19 通过这个进行数据时效性状态通知

```c++
void OnRecvDataTimeless(GD_Stock_Timeliness_Notification* pData);
```

| 参数    | 类型                                | 说明      |
| ----- | --------------------------------- | ------- |
| pData | GD_Stock_Timeliness_Notification* | 数据时效性通知 |
|       |                                   |         |

GD_Stock_Timeliness_Notification 各项参数说明：

| 参数名称   | 参数类型              | 说明                      |
| ------ | ----------------- | ----------------------- |
| isTick | bool              | True 为tick, false 为K线数据 |
| nType  | GD_TimelinessType | 数据时效性属性（注：参见**数据字典2**）  |
| szCode | GD_CodeType       | 代码名称                    |
|        |                   |                         |

| 类型别名        | 类型       | 描述   |
| ----------- | -------- | ---- |
| GD_CodeType | char[32] |      |
| GD_CodeType |          |      |

### 1.7.20 错误信息

```c++
void OnError(string error);
```

| 参数    | 类型     | 说明   |
| ----- | ------ | ---- |
| error | string | 错误信息 |
|       |        |      |





## 1.8 行情Api参数说明



### 1.8.1 登录认证服务器

```c++
bool Login(char* user, char* pass, int &err);
```

成功登陆，返回true；否则，返回false。

| 参数   | 类型    | 说明   |
| ---- | ----- | ---- |
| user | char* |      |
| pass | char* |      |
| err  | int   |      |
|      |       |      |

### 1.8.2 请求实时行情

tick数据和k线可以同时请求，ReqUpdateSubStockCode可以同时修改k线和tick的订阅代码。

#### 1.8.2.1 请求实时tick

```c++
void ReqRealtimeData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
```

| 参数          | 类型                    | 说明                                |
| ----------- | --------------------- | --------------------------------- |
| subCodes    | std::vector\<char*> & | 订阅代码列表                            |
| isAllMarket | bool                  | 是否订阅全市场代码                         |
| beginTime   | int                   | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| subDataType | int                   | 接收数据类型                            |
| err         | int &                 | 错误码返回                             |
|             |                       |                                   |

#### 1.8.2.2 请求实时k线

type为k线周期类型，一次只能订阅一种周期。其他参数同上，数据回调为 OnRecvGDKLine。

```c++
void ReqRealtimeGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
```

| 参数          | 类型                    | 说明                                |
| ----------- | --------------------- | --------------------------------- |
| type        | int                   | k线的周期类型                           |
| subCodes    | std::vector\<char*> & | 订阅代码列表                            |
| isAllMarket | bool                  | 是否订阅全市场代码                         |
| beginTime   | int                   | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| err         | int &                 | 错误码返回                             |
|             |                       |                                   |

#### 1.8.2.3 更新订阅代码

```c++
void ReqUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                    | 说明                                     |
| ----------- | --------------------- | -------------------------------------- |
| reqType     | GD_UpdateSubCodeType  | 更新订阅代码，可以增加、替换和删除订阅的代码。（注：参见**数据字典4**） |
| subCodes    | std::vector\<char*> & | 订阅代码列表                                 |
| isAllMarket | bool                  | 是否订阅全市场代码                              |
| err         | int &                 | 错误码返回                                  |
|             |                       |                                        |

### 1.8.3 请求模拟行情时间线

#### 1.8.3.1 

```c++
void ReqSimulationTimeline(GD_ISODateTimeType beginTime, GD_PlaybackSpeedType speadTyp, int &err);
```

| 参数        | 类型                   | 说明                        |
| --------- | -------------------- | ------------------------- |
| beginTime | GD_ISODateTimeType   | 请求历史数据模拟回测类型，参加**数据字典14** |
| speadTyp  | GD_PlaybackSpeedType | 请求历史数据模拟回测类型，参见**数据字典14** |
| err       | int &                | 错误码返回                     |
|           |                      |                           |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] | 日期类型 |
|                    |          |      |

#### 1.8.3.2 

```c++
void ReqSimulationTickData(std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int subDataType, int &err);
```

| 参数          | 类型                   | 说明   |
| ----------- | -------------------- | ---- |
| subCodes    | std::vector<char*> & |      |
| isAllMarket | bool                 |      |
| beginTime   | int                  |      |
| subDataType | int                  |      |
| int &       | err                  |      |
|             |                      |      |

#### 1.8.3.3

```c++
void ReqSimulationGDKlineData(int type, std::vector<char*> &subCodes, bool isAllMarket, int beginTime, int &err);
```

| 参数          | 类型                   | 说明   |
| ----------- | -------------------- | ---- |
| type        | int                  |      |
| subCodes    | std::vector<char*> & |      |
| isAllMarket | bool                 |      |
| beginTime   | int                  |      |
| err         | int &                |      |
|             |                      |      |

#### 1.8.3.4

```c++
void ReqSimulationUpdateSubStockCode(GD_UpdateSubCodeType reqType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                   | 说明                   |
| ----------- | -------------------- | -------------------- |
| reqType     | GD_UpdateSubCodeType | 更新订阅代码类型，参见**数据字典4** |
| subCodes    | std::vector<char*>   |                      |
| isAllMarket | bool                 |                      |
| err         | int                  |                      |
|             |                      |                      |



### 1.8.4 请求历史行情

tick数据和k线可以同时请求，ReqUpdateSubStockCode可以同时修改k线和tick的订阅代码。

#### 1.8.4.1 请求历史Level2 tick行情

modelType 为数据回放速度选择, fast为最快速，normal为与真实行情同样的速度。

```c++
void ReqHistoryData(GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, GD_PlaybackSpeedType modelType, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                   | 说明                                    |
| ----------- | -------------------- | ------------------------------------- |
| beginTime   | GD_ISODateTimeType   | 历史数据开始时间，精确到秒。例："2016-06-01 09:30:00" |
| endTime     | GD_ISODateTimeType   | 历史数据结束时间，精确到秒。例："2016-06-01 09:30:00" |
| modelType   | GD_PlaybackSpeedType | 修订操作类型选择，参见**数据字典14**                 |
| subCodes    | std::vector<char*> & | 订阅代码列表                                |
| isAllMarket | bool                 | 是否订阅全市场代码                             |
| err         | int &                | 错误码返回                                 |
|             |                      |                                       |

| 类型别名               | 类型       | 描述                              |
| ------------------ | -------- | ------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型(格式 yyyy-MM-dd hh:mm:ss) |
|                    |          |                                 |

#### 1.8.4.2 请求历史k线数据行情

数据回调为 OnRecvGDKLine。

```c++
void ReqHistoryGDKLineData(GD_CycType type, GD_ISODateTimeType beginTime, GD_ISODateTimeType endTime, std::vector<char*> &subCodes, bool isAllMarket, int &err);
```

| 参数          | 类型                    | 说明                                |
| ----------- | --------------------- | --------------------------------- |
| type        | GD_CycType            | 请求k线数据的周期类型，参见**数据字典1**           |
| beginTime   | GD_ISODateTimeType    | 开始时间，精确到秒。例："2016-06-01 09:30:00" |
| endTime     | GD_ISODateTimeType    | 结束时间，精确到秒。例："2016-06-01 09:30:00" |
| subCodes    | std::vector\<char*> & | 订阅代码表                             |
| isAllMarket | bool                  | 是否订阅全市场数据                         |
| err         | int &                 | 错误码返回（注：见数据字典**3**）               |
|             |                       |                                   |

| 类型别名               | 类型       | 描述                              |
| ------------------ | -------- | ------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型(格式 yyyy-MM-dd hh:mm:ss) |
|                    |          |                                 |

#### 1.8.4.3 查询的交易日列表

```c++
void ReqTradingDay(GD_ISODateTimeType beginDay, GD_ISODateTimeType endDay, int &err);
```

| 参数       | 类型                 | 说明    |
| -------- | ------------------ | ----- |
| beginDay | GD_ISODateTimeType | 开始时间  |
| endDay   | GD_ISODateTimeType | 结束时间  |
| err      | int &              | 错误码返回 |
|          |                    |       |

| 类型别名               | 类型       | 描述                              |
| ------------------ | -------- | ------------------------------- |
| GD_ISODateTimeType | char[21] | 日期和时间类型(格式 yyyy-MM-dd hh:mm:ss) |
|                    |          |                                 |

#### 

### 1.8.5 指标接口

#### 1.8.5.1

```c++
void calculateKLineByTick(std::vector<GD_CycType> cycs);
```

| 参数   | 类型                       | 说明   |
| ---- | ------------------------ | ---- |
| cycs | std::vector\<GD_CycType> | 指标接口 |
|      |                          |      |

#### 1.8.5.2

```c++
std::vector<GD_RestorationFactor> getRestorationFactor(std::vector<char*> &subCodes, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

| 参数        | 类型                   | 说明   |
| --------- | -------------------- | ---- |
| subCodes  | std::vector<char*> & |      |
| beginDate | GD_ISODateTimeType   |      |
| endDate   | GD_ISODateTimeType   |      |
| err       | int &                |      |
|           |                      |      |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |

#### 1.8.5.3

```c++
std::vector<GD_DetailMarketDayKline> getDetailMarketDayKline(std::vector<char*> &subCodes, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

| 参数        | 类型                   | 说明   |
| --------- | -------------------- | ---- |
| subCodes  | std::vector<char*> & |      |
| beginDate | GD_ISODateTimeType   |      |
| endDate   | GD_ISODateTimeType   |      |
| err       | int &                |      |
|           |                      |      |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |

#### 1.8.5.4 

```c++
vector<GD_StockFactors> getStockFactors(GD_CodeType code, vector<char*> &factorKeys, GD_ISODateTimeType beginDate, GD_ISODateTimeType endDate, int &err);
```

**Factor key** **说明** 参见**附录**。

| 参数         | 类型                 | 说明   |
| ---------- | ------------------ | ---- |
| code       | GD_CodeType        |      |
| factorKeys | vector<char*> &    |      |
| beginDate  | GD_ISODateTimeType |      |
| endDate    | GD_ISODateTimeType |      |
| err        | int &              |      |
|            |                    |      |

| 类型别名               | 类型       | 描述   |
| ------------------ | -------- | ---- |
| GD_ISODateTimeType | char[21] |      |
|                    |          |      |





## 1.9

```c++
const char* GetQuantPlatformApiVersion();
```

## 1.10

```c++
PT_QuantPlatform::GetDataApi* CreateGetDataApi(PT_QuantPlatform::GetDataSpi* spi, bool autoRecon, int reconTimeOut, bool autoReq = false, PT_QuantPlatform::TradeDataApi* tApi = NULL, bool enableLog = true);
```

| 参数               | 类型                              | 说明   |
| ---------------- | ------------------------------- | ---- |
| spi              | PT_QuantPlatform::GetDataSpi*   |      |
| autoRecon        | bool                            |      |
| reconTimeOut     | int                             |      |
| autoReq = false  | bool                            |      |
| tApi = NULL      | PT_QuantPlatform::TradeDataApi* |      |
| enableLog = true | bool                            |      |
|                  |                                 |      |

## 1.11

```c++
void DelGetDataApi(PT_QuantPlatform::GetDataApi* pAPI);
```

| 参数   | 类型                            | 说明   |
| ---- | ----------------------------- | ---- |
| pAPI | PT_QuantPlatform::GetDataApi* |      |
|      |                               |      |

## 1.12 使用示例代码

```c++
//行情接口使用示例

PT_QuantPlatform::GetDataApi* m_api = CreateGetDataApi(spi/*spi实例*/, true, 200, false);  // 创建行情实例

if (!m_api->connect("IP", Port ))	// 连接服务器
{
	return;
}

m_api->Login("user", "passwd", m_err);    // 登录

vector<char*> subCode;
subCode.push_back("600000");

GD_ISODateTimeType beginTime;
GD_ISODateTimeType endTime;
string beginStr = "2016-06-01 09:30:00";
string endStr = "2016-06-03 09:30:00";
strcpy(beginTime, beginStr.c_str());
strcpy(endTime, endStr.c_str());

m_api->ReqSimulationData(beginTime, endTime, fast_GD_SimuModelType, subCode, false, m_err);  //  请求历史level2
```

# 2 交易接口



## 2.1 系统构架

暂略

## 2.2 开发包文件结构

暂略

## 2.3 访问回调时序图

暂略

## 2.4创建回调函数实例

```c++
class TradeClient : public TradeDataSpi
{
public:
	virtual void OnDisConnect(){};
    //插入订单回调
	virtual void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, TD_ErrorCode error)
	{
		cout << "OrderInsert   error:" << error << " time:" << rsp->szInsertTime << " 			orderid:" << rsp->nOrderId << endl;
	};	
    //修改订单回调
	virtual void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, TD_ErrorCode error){};	     //删除订单回调	
	virtual void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, TD_ErrorCode error)
	{
		cout << "OnRspOrderDelete " << rsp->nOrderId << " error:" << error << endl;
	};				
	//查询订单回调
	virtual void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, TD_ErrorCode error, bool isEnd)
	{
		cout << "isEnd:" << isEnd << " orderId:" << rsp->nOrderId << " status:" 
        << rsp->nStatus << " dealprice" << rsp->nOrderPrice 
        << " dealvol:" << rsp->nOrderVol << endl;
	};	
    //查询成交回调
	virtual void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, TD_ErrorCode error, bool isEnd)
	{
		cout << "isEnd:" << isEnd << " orderId:" << rsp->nOrderId << " tradeid:" 
          << rsp->nMatchStreamId << " dealprice:" << rsp->nMatchPrice 
          << " deakvol:" << rsp->nMatchVol << endl;
	};	
    //查询持仓回调
	virtual void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, TD_ErrorCode error, bool isEnd){};			
    //订单状态变化通知
	virtual void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice)
	{
		cout << "OrderStatusChangeNotice   time:" << notice->szInsertTime 
          << " orderid:" << notice->nOrderId << " status:" << notice->nStatus << endl;
	};
    //成交状态更新通知
	virtual void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice)
	{
		cout << "OrderMatchNotice   tradeid:" << notice->nMatchStreamId << " time:" 
          << notice->szMatchTime << " price:" << notice->nMatchPrice << " vol:" 
          << notice->nMatchVol << endl;
	};						
	 // 查询资金帐号回调
	virtual void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, 
                                       TD_ErrorCode error, bool isEnd){}
     // 查询融券负债回调
	virtual void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, 
                                 TD_ErrorCode error, bool isEnd){}		
    // 查询最大可委托量回调
	virtual void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp,
                                        TD_ErrorCode error){}	
    // 查询可融券列表回调
	virtual void OnRspQrySecuritiesLendingAmount
      (const TD_QrySecuritiesLendingAmount_Rsp* rsp, TD_ErrorCode error, bool isEnd){}
public:
	TradeClient(){};
	~TradeClient(){};
};
```

## 2.5 获取交易连接对象实例

```c++
API_EXPORT PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool isSimulation = false, bool enableLog = true);
```

| 参数           | 类型                              | 说明                      |
| ------------ | ------------------------------- | ----------------------- |
| spi          | PT_QuantPlatform::TradeDataSpi* | 自定义的回调类的实例对象指针          |
| autoRecon    | bool                            | 是否断线后自动重连               |
| reconTimeOut | int                             | 断线重连重试时间间隔，单位毫秒。        |
| isSimulation | bool                            | 是否使用模拟撮合引擎；默认值为*false*。 |
| enableLog    | bool                            | 是否开启日志功能；默认值为*true*。    |
|              |                                 |                         |

## 2.6 释放交易连接对象实例

```c++
API_EXPORT void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
```

| 参数   | 类型                               | 说明          |
| ---- | -------------------------------- | ----------- |
| pAPI | (PT_QuantPlatform::TradeDataApi* | 需要释放的交易实例指针 |
|      |                                  |             |



## 2.7 交易Spi说明

### 2.7.1 用户登录回调

```c++
void OnRspUserTradeInfo(const TD_UserTradeInfoRsp *rsp;
```

| 参数   | 类型                    | 说明   |
| ---- | --------------------- | ---- |
| rsp  | TD_UserTradeInfoRsp * |      |
|      |                       |      |

### 2.7.2 连接成功

```c++
void OnTDConnect()；
```

### 2.7.3 断开

```c++
void OnTDDisConnect()；
```

### 2.7.4 断线重连尝试状态

```c++
void OnTDReconnectStatus(const bool successed)；
```

| 参数        | 类型   | 说明   |
| --------- | ---- | ---- |
| successed | bool |      |
|           |      |      |

### 2.7.5 插入订单回调

```c++
void OnRspOrderInsert(const TD_OrderInsert_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明     |
| ----- | -------------------------- | ------ |
| rsp   | const TD_OrderInsert_Rsp * | 插入订单回调 |
| error | int                        | 错误码    |
|       |                            |        |

TD_OrderInsert_Rsp 各项参数说明：

| 参数名称            | 参数类型               | 说明                             |
| --------------- | ------------------ | ------------------------------ |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）           |
| nUserInt        | int                | 用户保留字段                         |
| nUserDouble     | double             |                                |
| szUseStr        | char[128]          |                                |
| nUserId         | int                | 客户端编号                          |
| nAccountId      | int                | 券商资金账户Id                       |
| nOrderId        | int                | 服务器维护（服务唯一）                    |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）         |
| szContractCode  | char[32]           | 证券合约代码                         |
| szContractName  | char[32]           | 证券合约名称                         |
| nOrderType      | TD_OrderType       | 市价限价单（注：见数据字典**8**）            |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等（注：见数据字典**9**）     |
| nOffsetType     | TD_OffsetType      | 开平仓类型(注：见数据字典**10**)           |
| nOrderPrice     | double             | 申报价                            |
| nOrderVol       | int                | 申报量                            |
| szInsertTime    | char[32]           | 接收委托时间(格式 yyyy-MM-dd hh:mm:ss) |
| nStatus         | TD_OrderStatusType | 状态(见数据字典**11**)                |
| nDealedPrice    | double             | 成交均价                           |
| nDealedVol      | int                | 成交总量                           |
|                 |                    |                                |

### 2.7.3 修改订单回调

```c++
void OnRspOrderModify(const TD_OrderModify_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明                |
| ----- | -------------------------- | ----------------- |
| rsp   | const TD_OrderModify_Rsp * | 修改订单回调数据          |
| error | int                        | 错误码（注：见数据字典**7**） |
|       |                            |                   |

TD_OrderModify_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |
| nPrice      | double    | 修改申报价                |
| nVol        | int       | 修改申报量                |

### 2.7.4 删除订单回调

```c++
void OnRspOrderDelete(const TD_OrderDelete_Rsp *rsp, int error);
```

| 参数    | 类型                         | 说明                |
| ----- | -------------------------- | ----------------- |
| rsp   | const TD_OrderDelete_Rsp * | 删除订单回调数据          |
| error | int                        | 错误码（注：见数据字典**7**） |
|       |                            |                   |

TD_OrderDelete_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |

### 2.7.5 查询订单回调

```c++
void OnRspQryOrder(const TD_QryOrder_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                      | 说明       |
| ----- | ----------------------- | -------- |
| rsp   | const TD_QryOrder_Rsp * | 查询订单回调数据 |
| error | int                     | 错误码      |
| isEnd | bool                    | 是否是最后一条  |
|       |                         |          |

TD_QryOrder_Rsp 各项参数说明：

| 参数名称            | 参数类型               | 说明                             |
| --------------- | ------------------ | ------------------------------ |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）           |
| nUserInt        | int                | 用户保留字段                         |
| nUserDouble     | double             |                                |
| szUseStr        | char[128]          |                                |
| nUserId         | int                | 客户端编号                          |
| nAccountId      | int                | 券商资金账户Id                       |
| nOrderId        | int                | 服务器维护（服务唯一）                    |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）         |
| szContractCode  | char[32]           | 证券合约代码                         |
| szContractName  | char[32]           | 证券合约名称                         |
| nOrderType      | TD_OrderType       | 市价限价单（注：见数据字典**8**）            |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等(注：见数据字典**9**)     |
| nOffsetType     | TD_OffsetType      | 开平仓类型（注：见数据字典**10**）           |
| nOrderPrice     | double             | 申报价                            |
| nOrderVol       | int                | 申报量                            |
| szInsertTime    | char[32]           | 接收委托时间(格式 yyyy-MM-dd hh:mm:ss) |
| nStatus         | TD_OrderStatusType | 状态（注：见数据字典**11**）              |
| nDealedPrice    | double             | 成交均价                           |
| nDealedVol      | int                | 成交总量                           |
|                 |                    |                                |

### 2.7.6 查询成交回调

```c++
void OnRspQryMatch(const TD_QryMatch_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                      | 说明                |
| ----- | ----------------------- | ----------------- |
| rsp   | const TD_QryMatch_Rsp * | 查询成交回调数据          |
| error | int                     | 错误码(注：见数据字典**7**) |
| isEnd | bool                    | 是否是最后一条           |

TD_QryMatch_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 对于委托编号               |
| nMatchStreamId | int       | 成交系统编号               |
| nMatchPrice    | double    | 成交价                  |
| nMatchVol      | int       | 成交量                  |
| szContractCode | char[32]  | 股票代码                 |
| szMatchTime    | char[21]  | 成交时间                 |

### 2.7.7 查询持仓回调

```c++
void OnRspQryPosition(const TD_QryPosition_Rsp *rsp, int error, bool isEnd);
```

| 参数    | 类型                         | 说明                |
| ----- | -------------------------- | ----------------- |
| rsp   | const TD_QryPosition_Rsp * | 查询持仓回调数据          |
| error | int                        | 错误码(注：见数据字典**7**) |
| isEnd | bool                       | 是否是最后一条           |

TD_QryPosition_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 证券合约代码               |
| nPosition      | int       | 持仓总量                 |
| nPrice         | double    | 持仓均价                 |
| nProfit        | double    | 浮盈                   |

### 2.7.8 查询资金帐号回调

```c++
void OnRspQryCapitalAccount(const TD_QryCapital_Rsp* rsp, int error, bool isEnd);
```

| 参数    | 类型                       | 说明                |
| ----- | ------------------------ | ----------------- |
| rsp   | const TD_QryCapital_Rsp* | 查询资金账号回调数据        |
| error | int                      | 错误码（注：见数据字典**7**） |
| isEnd | bool                     | 是否是最后一条           |

TD_QryCapital_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| m_fundbal   | double    | 资金负债总额               |
| m_fundavl   | double    | 资金可用金额               |

### 2.7.9 查询融券负债回调

```c++
void OnRspQrySecuDebt(const TD_QrySecuDebt_Rsp* rsp, int error, bool isEnd); 
```

| 参数    | 类型                        | 说明                |
| ----- | ------------------------- | ----------------- |
| rsp   | const TD_QrySecuDebt_Rsp* | 查询融券负债回调数据        |
| error | int                       | 错误码(注：见数据字典**7**) |
| isEnd | bool                      | 是否是最后一条           |
|       |                           |                   |

TD_QrySecuDebt_Rsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                  |
| -------------- | --------- | ------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID |
| nUserInt       | int       | 用户保留字段              |
| nUserDouble    | double    |                     |
| szUseStr       | char[128] |                     |
| nUserId        | int       | 客户端编号               |
| nAccountId     | int       | 券商资金账户Id            |
| szContractCode | char[32]  | 股票代码                |
| m_dstkbal      | int       | 负债总股数               |

### 2.7.10 查询最大可委托量回调

```c++
void OnRspQryMaxEntrustCount(const TD_QryMaxEntrustCount_Rsp* rsp, int error);
```

| 参数    | 类型                               | 说明                |
| ----- | -------------------------------- | ----------------- |
| rsp   | const TD_QryMaxEntrustCount_Rsp* | 查询最大可成交量回调数据      |
| error | int                              | 错误码（注：见数据字典**7**） |
|       |                                  |                   |

TD_QryMaxEntrustCount_Rsp 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| m_maxStkqty | int       | 最大可委托数量              |

### 2.7.11 查询可融券列表回调

```c++
void OnRspQrySecuritiesLendingAmount(const TD_QrySecuritiesLendingAmount_Rsp* rsp, int error, bool isEnd); 
```

| 参数    | 类型                                       | 说明                |
| ----- | ---------------------------------------- | ----------------- |
| rsp   | const TD_QrySecuritiesLendingAmount_Rsp* | 查询可融券列表回调数据       |
| error | int                                      | 错误码(注：见数据字典**7**) |
| isEnd | bool                                     | 是否是最后一条           |
|       |                                          |                   |

TD_QrySecuritiesLendingAmountRsp 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 股票代码                 |
| m_sepremQty    | int       | 余券                   |
|                |           |                      |

### 2.7.12 订单状态变化通知

```c++
void OnRtnOrderStatusChangeNotice(const TD_OrderStatusChangeNotice *notice);
```

| 参数     | 类型                                 | 说明         |
| ------ | ---------------------------------- | ---------- |
| notice | const TD_OrderStatusChangeNotice * | 订单状态变化通知数据 |
|        |                                    |            |

TD_OrderStatusChangeNotice 各项参数说明：

| 参数名称            | 参数类型               | 说明                         |
| --------------- | ------------------ | -------------------------- |
| nReqId          | int                | 请求ID（有客户端API维护的唯一ID）       |
| nUserInt        | int                | 用户保留字段                     |
| nUserDouble     | double             |                            |
| szUseStr        | char[128]          |                            |
| nUserId         | int                | 客户端编号                      |
| nAccountId      | int                | 券商资金账户Id                   |
| nOrderId        | int                | 服务器维护（服务唯一）                |
| szOrderStreamId | char[32]           | 委托编号（broker 或交易所的唯一编号）     |
| szContractCode  | char[32]           | 证券合约代码                     |
| szContractName  | char[32]           | 证券合约名称                     |
| nOrderType      | TD_OrderType       | 市价限价单(注：见数据字典**8**)        |
| nTradeType      | TD_TradeType       | 交易类型 买、卖、融券等（注：见数据字典**9**） |
| nOffsetType     | TD_OffsetType      | 开平仓类型（注：见数据字典**10**）       |
| nOrderPrice     | double             | 申报价                        |
| nOrderVol       | int                | 申报量                        |
| szInsertTime    | char[21]           | 接收委托时间                     |
| nStatus         | TD_OrderStatusType | 状态(注：见数据字典**11**)          |
| nDealedPrice    | double             | 成交均价                       |
| nDealedVol      | int                | 成交总量                       |
|                 |                    |                            |

### 2.7.13 成交状态更新通知

```c++
void OnRtnOrderMatchNotice(const TD_OrderMatchNotice *notice);
```

| 参数     | 类型                          | 说明         |
| ------ | --------------------------- | ---------- |
| notice | const TD_OrderMatchNotice * | 成交状态更新通知数据 |
|        |                             |            |

TD_OrderMatchNotice 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 对于委托编号               |
| nMatchStreamId | int       | 成交系统编号               |
| nMatchPrice    | double    | 成交价                  |
| nMatchVol      | int       | 成交量                  |
| szContractCode | char[32]  | 股票代码                 |
| szMatchTime    | char[21]  | 成交时间                 |
|                |           |                      |

## 2.8 交易Api说明

### 2.8.1 登录

```c++
bool Login(char* user, char* pass, int &err);
```

登录成功，返回true；否则，返回false，且将错误码修改至`err。

| 参数   | 类型    | 说明                  |
| ---- | ----- | ------------------- |
| user | char* | 登录用户名               |
| pass | char* | 登录密码                |
| err  | int   | 错误码返回(注：见数据字典**3**) |
|      |       |                     |

### 2.8.2 

```c++
void SetNewBackTest(double stampTax, double transferFees, double commissions, char* szComment, int &err);
```

| 参数           | 类型     | 说明   |
| ------------ | ------ | ---- |
| stampTax     | double |      |
| transferFees | double |      |
| commissions  | double |      |
| szComment    | char*  |      |
| err          | int &  |      |
|              |        |      |



### 2.8.3 插入订单

```c++
void OrderInsert(TD_OrderInsert_Req* req);
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_OrderInsert_Req* | 插入订单数据 |
|      |                     |        |

TD_OrderInsert_Req 各项参数说明

| 参数名称            | 参数类型          | 说明                         |
| --------------- | ------------- | -------------------------- |
| nReqId          | int           | 请求ID（有客户端API维护的唯一ID）       |
| nUserInt        | int           | 用户保留字段                     |
| nUserDouble     | double        |                            |
| szUseStr        | char[128]     |                            |
| nUserId         | int           | 客户端编号                      |
| nAccountId      | int           | 券商资金账户Id                   |
| nOrderId        | int           | 服务器维护（服务唯一）                |
| szOrderStreamId | char[32]      | 委托编号（broker 或交易所的唯一编号）     |
| szContractCode  | char[32]      | 证券合约代码                     |
| szContractName  | char[32]      | 证券合约名称                     |
| nOrderType      | TD_OrderType  | 市价限价单(注：见数据字典**8**)        |
| nTradeType      | TD_TradeType  | 交易类型 买、卖、融券等（注：见数据字典**9**） |
| nOffsetType     | TD_OffsetType | 开平仓类型（注：见数据字典**10**）       |
| nOrderPrice     | double        | 申报价                        |
| nOrderVol       | int           | 申报量                        |
| szInsertTime    | char[21]      | 接收委托时间                     |
|                 |               |                            |

### 2.8.4 修改订单

```c++
void OrderModify(TD_OrderModify_Req* req);
```

| 参数   | 类型                  | 说明   |
| ---- | ------------------- | ---- |
| req  | TD_OrderModify_Req* | 修改订单 |
|      |                     |      |

TD_OrderModify_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       | 订单Id                 |
| nPrice      | double    | 修改申报价                |
| nVol        | int       | 修改申报量                |
|             |           |                      |

### 2.8.5 删除订单

```c++
void OrderDelete(TD_OrderDelete_Req* req);
```

| 参数   | 类型                  | 说明   |
| ---- | ------------------- | ---- |
| req  | TD_OrderDelete_Req* | 删除订单 |
|      |                     |      |

TD_OrderDelete_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
| nOrderId    | int       |                      |
|             |           |                      |

### 2.8.6 查询当日所有订单

```c++
void QryOrder(TD_QryOrder_Req* req);
```

| 参数   | 类型               | 说明       |
| ---- | ---------------- | -------- |
| req  | TD_QryOrder_Req* | 查询当日所有订单 |
|      |                  |          |

TD_QryOrder_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| nOrderId       | int       | 委托编号                 |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.7 查询所有成交

```c++
void QryMatch(TD_QryMatch_Req* req);
```

| 参数   | 类型               | 说明     |
| ---- | ---------------- | ------ |
| req  | TD_QryMatch_Req* | 查询所有成交 |
|      |                  |        |

TD_QryMatch_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.8 查询头寸

```c++
void QryPosition(TD_QryPosition_Req* req);
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_QryPosition_Req* | 查询所有头寸 |
|      |                     |        |

TD_QryPosition_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户信息             |
| szContractCode | char[32]  | 证券合约代码               |
|                |           |                      |

### 2.8.9 查询资金帐号

```c++
void QryCapitalAccount(TD_QryCapital_Req* req);
```

| 参数   | 类型                 | 说明     |
| ---- | ------------------ | ------ |
| req  | TD_QryCapital_Req* | 查询资金账号 |
|      |                    |        |

TD_QryCapital_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
|             |           |                      |

### 2.8.10 查询融券负债

```c++
void QrySecuDebt(TD_QrySecuDebt_Req* req);  
```

| 参数   | 类型                  | 说明     |
| ---- | ------------------- | ------ |
| req  | TD_QrySecuDebt_Req* | 查询融券负债 |
|      |                     |        |

TD_QuerySecuDebt_Req 各项参数说明：

| 参数名称        | 参数类型      | 说明                   |
| ----------- | --------- | -------------------- |
| nReqId      | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt    | int       | 用户保留字段               |
| nUserDouble | double    |                      |
| szUseStr    | char[128] |                      |
| nUserId     | int       | 客户端编号                |
| nAccountId  | int       | 券商资金账户Id             |
|             |           |                      |

### 2.8.11 查询最大可委托量

```c++
void QryMaxEntrustCount(TD_QryMaxEntrustCount_Req* req);
```

| 参数   | 类型                           | 说明       |
| ---- | ---------------------------- | -------- |
| req  | TD_QueryMaxEntrustCount_Req* | 查询最大可委托量 |
|      |                              |          |

TD_QryMaxEntrustCount_Req 各项参数说明：

| 参数名称           | 参数类型         | 说明                   |
| -------------- | ------------ | -------------------- |
| nReqId         | int          | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int          | 用户保留字段               |
| nUserDouble    | double       |                      |
| szUseStr       | char[128]    |                      |
| nUserId        | int          | 客户端编号                |
| nAccountId     | int          | 券商资金账户Id             |
| szContractCode | char[32]     | 股票代码                 |
| nPrice         | double       | 价格                   |
| nTraderType    | TD_TradeType | 交易行为(注：见数据字典**9**)   |
|                |              |                      |

### 2.8.12 查询可融券列表

```c++
void QrySecuritiesLendingAmount(TD_QrySecuritiesLendingAmount_Req* req);
```

| 参数   | 类型                                 | 说明      |
| ---- | ---------------------------------- | ------- |
| req  | TD_QrySecuritiesLendingAmount_Req* | 查询可融券列表 |
|      |                                    |         |

QrySecuritiesLendingAmount_Req 各项参数说明：

| 参数名称           | 参数类型      | 说明                   |
| -------------- | --------- | -------------------- |
| nReqId         | int       | 请求ID（有客户端API维护的唯一ID） |
| nUserInt       | int       | 用户保留字段               |
| nUserDouble    | double    |                      |
| szUseStr       | char[128] |                      |
| nUserId        | int       | 客户端编号                |
| nAccountId     | int       | 券商资金账户Id             |
| szContractCode | char[32]  | 股票代码                 |
|                |           |                      |



## 2.9 

```c++
PT_QuantPlatform::TradeDataApi* CreateTradeDataApi(PT_QuantPlatform::TradeDataSpi* spi, bool autoRecon, int reconTimeOut, bool isSimulation = false, bool enableLog = true);
```

| 参数           | 类型                              | 说明   |
| ------------ | ------------------------------- | ---- |
| spi          | PT_QuantPlatform::TradeDataSpi* |      |
| autoRecon    | bool                            |      |
| reconTimeOut | int                             |      |
| isSimulation | bool                            |      |
| enableLog    | bool                            |      |
|              |                                 |      |



## 2.10 

```c++
void DelTradeDataApi(PT_QuantPlatform::TradeDataApi* pAPI);
```

| 参数   | 类型                              | 说明   |
| ---- | ------------------------------- | ---- |
| pAPI | PT_QuantPlatform::TradeDataApi* |      |
|      |                                 |      |



## 2.11 使用示例代码

```c++
//1、使用模拟引擎
TradeDataApi* m_tApi = CreateTradeDataApi(this, true, 200); 
// 创建模拟交易实例，不需连接、登录操作，可直接进行功能请求



//2、使用交易服务器
radeDataApi* m_tApi = CreateTradeDataApi(this, true, 200, true);  // 创建交易实例

if (!m_tApi->connect("IP", Port))  // 连接服务器
{
	return;	
}

if (!m_tApi->Login())  // 登陆
{
	return;	
}

```



# 3 数据字典

#### 数据字典 1

| 序号   | 字典项                               | 字典项名称         |
| ---- | --------------------------------- | ------------- |
| 1    | GD_CycType                        |               |
|      | none_GD_CycType                   | 空             |
|      | second_10_GD_CycType              | 10秒           |
|      | minute_GD_CycType                 | 分             |
|      | minute_5_GD_CycType               | 5分            |
|      | minute_15_GD_CycType              | 15分           |
|      | minute_30_GD_CycType              | 30分           |
|      | hour_GD_CycType                   | 小时            |
|      | day_GD_CycType                    | 日             |
| 2    | GD_TimelinessType                 | 数据效性          |
|      | historyData_GD_TimelinessType     | 历史数据          |
|      | realtimeData_GD_TimelinessType    | 实时数据          |
| 3    | GD_ErrorType                      |               |
|      | none_GD_ErrorType                 | 无             |
|      | userError_GD_ErrorType            | 用户不存在或用户名密码错误 |
|      | overLoginNumError_GD_ErrorType    | 登录数超限         |
|      | serverConnectedError_GD_ErrorType | 服务器连接错误       |
| 4    | GD_UpdateSubCodeType              |               |
|      | add_GD_UpdateSubCodeType          | 添加订阅代码        |
|      | remove_GD_UpdateSubCodeType       | 移除已有订阅代码      |
|      | replace_GD_UpdateSubCodeType      | 替换全部订阅代码      |
| 5    | GD_SimuModelType                  | 请求历史数据模拟回测类型  |
|      | fast_GD_SimuModelType             | 快速模式          |
|      | normal_GD_SimuModelType           | 正常模式          |
| 6    | TD_BrokerType                     | 券商类型          |
|      | TD_BrokerType_None                |               |
|      | TD_BrokerType_dongwu              |               |
|      | TD_BrokerType_guangda             |               |
|      | TD_BrokerType_guotai              |               |
|      | TD_BrokerType_guoxin              |               |
|      | TD_BrokerType_haitong             |               |
|      | TD_BrokerType_shenwan             |               |
|      | TD_BrokerType_yinhe               |               |
|      | TD_BrokerType_zhaoshang           |               |
|      | TD_BrokerType_fangzheng           |               |
|      | TD_BrokerType_AC                  |               |
|      | TD_BrokerType_zhongxin            |               |
|      | TD_BrokerType_anxin               |               |
|      | TD_BrokerType_dongbei             |               |
|      | TD_BrokerType_huataiwang          |               |
|      | TD_BrokerType_hengtai             |               |
|      | TD_BrokerType_zhongjing           |               |
|      | TD_BrokerType_guangfa             |               |
|      | TD_BrokerType_huabao              |               |
|      | TD_BrokerType_xuntou              |               |
|      | TD_BrokerType_xibu                |               |
|      | TD_BrokerType_IMSWT               |               |
|      | TD_BrokerType_huatai              |               |
| 7    | TD_ErrorCode                      |               |
|      | TD_ErrorCodeEnum_None             |               |
|      | TD_ErrorCodeEnum_NoOrder          |               |
|      | TD_ErrorCodeEnum_FinishedOrder    |               |
|      | TD_ErrorCodeEnum_WrongOrder       |               |
|      | TD_ErrorCodeEnum_WrongModifyOrder |               |
|      | TD_ErrorCodeEnum_SendFailed = 100 |               |
|      | TD_ErrorCodeEnum_NOT_TRADING_TIME |               |
|      | TD_ErrorCodeEnum_Unknown          |               |
| 8    | TD_OrderType_Limit                | 限价单           |
|      | TD_OrderType_Market               | 市价单           |
| 9    | TD_TradeType_Sell                 | 普通卖出          |
|      | TD_TradeType_SellBySecuLending    | 融券卖出          |
|      | TD_TradeType_SellSecurityRtnCash  | 卖券还款          |
|      | TD_TradeType_None                 |               |
|      | TD_TradeType_RtnSecurity          | 直接还券          |
|      | TD_TradeType_RtnCash              | 直接还款          |
|      | TD_TradeType_Buy                  | 普通买入          |
|      | TD_TradeType_BuyOnMargin          | 融资买入          |
|      | TD_TradeType_BuySecurityRtnSecu   | 买券还券          |
| 10   | TD_OffsetType_Open                | 开仓            |
|      | TD_OffsetType_Close               | 平仓            |
| 11   | TD_OrderStatusType_fail           | 指令失败          |
|      | TD_OrderStatusType_partRemoved    | 部分撤单          |
|      | TD_OrderStatusType_removed        | 撤单成功          |
|      | TD_OrderStatusType_allDealed      | 全部成交          |
|      | TD_OrderStatusType_unAccpet       | 未接受           |
|      | TD_OrderStatusType_accpeted       | 已接受未受理        |
|      | TD_OrderStatusType_queued         | 正在排队	(已受理状态)  |
|      | TD_OrderStatusType_toModify       | 待报改单          |
|      | TD_OrderStatusType_modifing       | 已报改单          |
|      | TD_OrderStatusType_modified       | 改单受理          |
|      | TD_OrderStatusType_toRemove       | 待报撤单          |
|      | TD_OrderStatusType_removing       | 已报待撤          |
|      | TD_OrderStatusType_partDealed     | 部分成交          |
| 12   | TD_OffsetType                     |               |
|      | TD_OffsetType_None                |               |
|      | TD_OffsetType_Open                | 开仓            |
|      | TD_OffsetType_Close               | 平仓            |
| 13   | GD_ErrorType                      |               |
|      | none_GD_ErrorType                 | 无             |
|      | userError_GD_ErrorType            | 用户不存在或用户名密码错误 |
|      | overLoginNumError_GD_ErrorType    | 登录数超限         |
|      | serverConnectedError_GD_ErrorType | 服务器连接错误       |
|      |                                   |               |

#### 数据字典 2

| 序号   | 字典项                           | 字典名称         |
| ---- | ----------------------------- | ------------ |
| 14   | GD_PlaybackSpeedType          | 请求历史数据模拟回测类型 |
|      | fast_GD_PlaybackSpeedType     | 快速模式         |
|      | normal_GD_PlaybackSpeedType   | 正常模式         |
|      | x2Spped_GD_PlaybackSpeedType  | 2倍速模式        |
|      | x3Spped_GD_PlaybackSpeedType  | 3倍速模式        |
|      | x5Spped_GD_PlaybackSpeedType  | 5倍速模式        |
|      | x10Spped_GD_PlaybackSpeedType | 10倍速模式       |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |
|      |                               |              |



## 4 附录 factor key 说明     因子的计算方式、含义 

factor key 的类型均为double。

### 4.1 ACD （包含ACD20、ACD6）

#### 4.1.1 指标含义

ACD，收集派发指标（Accumulative Distribution），是分析收盘价、最高价、最低价与涨跌关系的市场循环指标；该指标将市场分为两股收集（买入）及派发（估出）的力量，属于均线型因子。

#### 4.1.2 指标线

PT_QuantPlatform 中出现的ACD指标主要分为20日、30日收集派发指标，即ACD20、ACD6。

#### 4.1.3 应用法则

① ACD线下降，而股价上升时，为卖出信号；

② ACD线上升，而股价下降时，为买进信号；

③ ACD指标上穿其20日（或6日）均线时，为买进信号（参见图1）；

④ ACD指标跌穿其20日（或6日）均线时，为卖出信号（参见图2）。

 ![ACD](C:\Users\Administrator\Desktop\ACD.jpg)

图1 ACD指标上穿20日均线

 ![ACD20 跌穿](C:\Users\Administrator\Desktop\ACD20 跌穿.jpg)

图2 ACD指标跌穿20日均线



### 4.2 AD （包含AD、AD20、AD6，A/D或AC）

#### 4.2.1 指标含义

AD，累积/派发线（Accumulation / Distribution Line），该指标将每日的成交量通过价格加权累计，用以计算成交的动量，属于趋势型因子。其原理与OBV类似。

#### 4.2.2 指标线

PT_QuantPlatform 中出现的AD指标主要分为AD、AD20、AD6。

#### 4.2.3 计算方法

① Ac = 昨日AC+多空对比*今日成交量

② 多空对比 = [ ( 收盘价-最低价 ) - ( 最高价 - 收盘价 ) ] /  (最高价 - 最低价 )

若最高价等于最低价（如直接封停板），则优化处理为：多空对比 = ( 收盘价 / 昨收盘 ) - 1

#### 4.2.4 应用法则

① A/D测量资金流向，向上的A/D表明买房占优势，向下的A/D表明卖方占优势；

② A/D与价格的背离可视为买卖信号，即底背离考虑买入，顶背离考虑卖出；

③ 应当注意A/D忽略了缺口的影响，事实上，跳空缺口的意义是不能轻易忽略的。

④ A/D指标无需设置参数，但是在应用时，可以结合指标的均线进行分析。 



### 4.3 ADTM（包含SBM,STM） 

#### 4.3.1 指标含义

ADTM，动态买卖气指标，用开盘价的向上波动幅度和向下波动幅度的距离差值来描述人气高低的指标，属于超买超卖型因子。此外，计算动态买卖气指标的M日的移动平均线为ADTMMA。

#### 4.3.2 计算公式

① 当日开盘价 ≤ 昨日开盘价，DTM = 0；如果当日开盘价 ＞ 昨日开盘价，DTM = ( 当日最高价 - 开盘价 ) 和 ( 当日开盘价 - 昨日开盘价 ) 的较大值。

② 当日开盘价 ≥ 昨日开盘价，DBM = 0；如果当日开盘价 ＜ 昨日开盘价，DBM = ( 当日开盘价 - 最低价 ) 和 ( 昨日开盘价 - 开盘价 ) 的较大值。

③ STM = DTM 在N日内的和。

④ SBM = DBM在N日内的和。

⑤ 如果STM ＞ SBM，ADTM = ( STM - SBM ) / STM，ADTM = 0。

⑥ ADTMMA = ADTM的M日简单移动平均。

⑦ 参数N设为23日，参数M设置为8日。

#### 4.3.3 应用法则

① ADTM指标在+1到-1之间波动；低于-0.5时，为低风险区；高于+0.5时，为高风险区（参见图3）。

② ADTM上穿ADTMMA时，买入股票；ADTM跌穿ADTMMA时，卖出股票（参见图4）。

 ![ADTM](C:\Users\Administrator\Desktop\ADTM.jpg)

图3 ADTM高风险区

 ![ADTM买卖jpg](C:\Users\Administrator\Desktop\ADTM买卖jpg.jpg)

图4 ADTM穿ADTMMA

### 4.4 ADX

#### 4.4.1 指标含义

ADX，平均趋向指数（Average Directional Index 或者Average Directional Movement Index），该指数反应的是趋向变动的程度，而不是方向的本身。属于趋势型因子。

#### 4.4.2 应用法则

① 进场与出场是采用+DI14与-DI14的穿越信号。

② 当DI发生穿越信号时，取当天的极端点作为止损点；。

③ 当ADX的位置高于两条DI而方向发生改变，即为趋势反转的早期信号，可做部分的获利了结。最后的平仓信号是来自于DI穿越或极端点的止损被引发。当ADX改变方向时，如果+DI14高于-DI14，这代表趋势的变动是由上亦下，反之亦然。

④ 如果ADX高于两条DI，而且读数明显偏高，表明当前处于超买/超卖状态，顺势的新交易头寸通常很难获利。

⑤ 如果ADX同时低于两条DI，则避免采用顺势交易的系统，因为市场中没有明显的趋势。

⑥ 如果ADX的读数低于20~25，不论它与两条DI的相对位置如何，都要避免采用顺势交易的系统。

#### 4.4.3 应用示例

ADX线代表力量的强弱，走势随+DI和-DI力量强的一方发展。

在ADX为黄线，+DI为红线，-DI为绿线的前提下：红线上行，绿线下行，且黄线与上行线同行，则价格上涨；如果绿线上行，红线下行，且黄线与上行线同行，则价格下跌。如图5所示。

 ![ADX](C:\Users\Administrator\Desktop\ADX.jpg)

图5 ADX指标指示的做多、做空位置

#### 4.4.4 ADX的相关指标——ADXR

ADXR为ADX与ADX倒数第六天数值的相加后再除以2。

计算公式：(ADX + REF(ADX , M)) / 2，m = 6。



### 4.5 APBMA

#### 4.5.1 指标含义

APBMA，绝对偏差移动平均（Absolute Price Bias Moving Average）。考察一段时期内价格偏离均线的移动平均。属于均线型因子。



### 4.6 AR

#### 4.6.1 指标含义

人气指标，是以当天开市价为基础，即以当天市价分别比较当天最高，最低价，通过一定时期内开市价在股价中的地位，反映市场买卖人气。属于能量型因子。与AR类似的是BR，两者均以历史股价为技术指标。

#### 4.6.2 计算公式

最近N日内最高价与收盘价的差的和除以开盘价与最低价的差的和，所得的比值放大100。该指标又可称为买卖气势指标。
$$
\begin{equation*}
AR = 100 \times  \sum_{i=1}^n{(H-O)} / \sum_{i=1}^n{(O-L)}
\end{equation*}
$$
注：H——当天最高价；L——当天最低价；O——当天开盘价；n——待设定参数，缺省值26日。

#### 4.6.3 应用法则

① 通常AR的走势与股价是同向的，即AR下跌，则大势也跌。

② 在头部或底部即将形成时，AR往往具有领先的功能。

③ AR值以100为中心地带，在80 ~ 120之间波动较为正常，属于盘整行情，股价走势比较平稳，不会出现剧烈波动。

④ AR值走高时表示行情活跃，过高则表示股价进入高价，AR指标上升至150以上时，就必须注意股价将进入回档或下跌。

⑤ AR值走低，表示人气衰退，需要充实，过低则暗示股价可能跌入低谷，在50以下，可考虑伺机介入。

⑥ 从AR曲线可以看出一段时期的买卖气势，并具有先于股价到达峰或跌入谷底的功能。



### 4.7 ARBR

#### 4.7.1 指标含义

人气指标（AR）和意愿指标（BR）都是以分析历史股价为手段的技术指标，ARBR使用AR减去BR得到的值。属于能量型因子。

#### 4.7.2 计算公式

ARBR = AR - BR

注：AR、BR的计算公式，参见AR、BR指标。

#### 4.7.3 应用法则

① 买卖信号：当ARBR曲线在100附近盘整了较长一段时间以后，一旦ARBR曲线几乎同时由下向上突破50这条线，并且股价也放量突破中期均线，则意味着股票中期强势行情即将开始，即为ARBR指标发出的中线买入信号。当ARBR曲线从高位向下滑落，一旦ARBR曲线又接着突破了100以后，如果股价同时也突破中长期均线，则意味着股票的短期强势行情可能结束，这是ARBR指标发出的短线卖出信号。此时，投资者应该及时卖出股票。

② 持股持币信号：当ARBR曲线一直运行在100线上方，同时股价也依托中短期均线强势上攻时，则表明股价是处于极强势的上涨行情，这是ARBR指标发出的短线持股看涨信号。当ARBR曲线向下突破100线以后，一直运行在100线下方，同时股价也被中短期均线压制下行时，则表明股价的中期弱势形成，这是ARBR指标发出的持币待涨信号。



### 4.8 ARC 

#### 4.8.1 指标含义

ARC，变化率指数均值，股票的价格变化率RC指标的均值，用以判断前一段交易周期内股票的平均价格变化率。属于超买超卖型因子。



### 4.9 Aroon （包含Aroon、AroonDown、AroonUp）

#### 4.9.1 指标含义

Aroon，通过计算自价格达到近期最高值和最低值以来所经过的期间数，帮助投资者预测证券价格从趋势到区域区域或反转的变化，属于趋势型因子。

#### 4.9.2 指标线

Aroon指标分为Aroon、AroonUp和AroonDown3个具体指标。

#### 4.9.3 计算公式

AroonUp = [ ( 计算期天数 - 最高价后的天数 ) / 计算期天数 ] * 100

AroonDown = [ ( 计算期天数 - 最低价后的天数 ) / 计算期天数 ] * 100

使用公式时，需要先设定一个时间段（或者周期），一般为25天，这个区间内创出收盘最高价的那天到起始日的时间距离作为分子，除以25天，即为AroonUp指标；它反映了有多长时间，股价走势在近期最高点之下。AroonDown指标的计算方式法及意义与之相似，只是将“收盘最高价”换成“收盘最低价”。与这两个指标相关联的AROON Osc，是用AroonUp减去AroonDown得到的。

#### 4.9.4 应用法则

在分析Aroon指标时，主要观察三种状态：

① 极值0与100 当Up线达到100时，市场处于多头强势；如果维持在70 ~ 100之间，表示处于多头上升趋势；同样，如果Down线达到100时，市场处于空头强势；如果维持在70 ~ 100之间，表示处于空头下降趋势。当Up线达到0时，表示多头处于极弱势，如果维持在0 ~ 30之间，表明多头处于较弱势；当Down线达到0时，表示空头处于极弱势，如果维持在0 ~ 30之间，表明空头处于较弱势。如果两条线同处于底部，表示处于盘整时期，无趋势。

② 平行运动：如果两条线平行运动时，表明市场原有趋势仍在继续，只到由极值水平或交叉穿行而改变市场方向为止。

③ 交叉穿行：当下行线上穿上行线时，表明原有趋势逐渐减弱，预计趋势将开始反转。反之亦然。

实时研判：

① AroonUp、AroonDown可以研判一个新趋势的开始：高于70，表示强势；低于50，趋势正在减弱；两线移近底部，表明即将盘整。

② Aroon震荡线高于0，表示上升趋势；低于0，表示下降趋势，偏离0线越远，走势越强。



### 4.10 ASI

#### 4.10.1 指标含义

ASI，累计震动升降指标（Accumulation Swing Index），又称实质线，ASI企图以开盘、最高、最低、收盘价构筑成一条幻想线，以便取代目前的走势，形成最能表现当前市况的真实市场线（Real Market）。

#### 4.10.2 计算公式

① 先计算出当天最高价与前一天收盘价的绝对值A、当天最低价与前一天收盘价的绝对差B、当天最高价与前一天最低价的绝对值C、前一天收盘价与前一天开盘价的绝对差D，比较A、B、C三者之间的最大值，若A最大，则R = A+1 / 2 * B+ 1 / 4 * D；若B最大，则R = B + 1 / 2 * A + 1 / 4 * D；若C最大，则R = C + 1 / 4 * D。

② X = E + 1 / 2 * F + G

注： E = 当天收盘价 - 前一天收盘价

​        F = 当天收盘价 - 当天开盘价

​       G = 前一天收盘价 - 前一天开盘价

 ③ SI = 50 * X / R * K / L

​       K = A、B两者之间的最大者

​       L = 3

④ ASI = 累计每日之SI值。

#### 4.10.3 应用法则

ASI大部分时机都是和股价走势同步的，投资者仅能从众多股票中寻找少数产生领先突破的个股。若ASI领先股价，提早突破前次ASI高点或低点，则次一日之后，股价必然能突破前次高点或低点。具体情况如下：

① 当股价由下往上，欲穿过前一波的高点套牢区时，于接近近高点处，尚未确定能否顺利穿越之际，如果AIS领先股价，提早一步，通过相对股价的前一波ASI高点，则次一日之后，股价必然能顺利突破高点的套牢区。股民可以把握ASI的领先作用，提前买入股票。

② 当股价由上往下，欲穿越前一波低点的密集支撑区时，于接近低点处，尚未确定股价是否会跌破支撑之际，如果ASI领先股价，提早一步，跌破相对股价的前一波ASI低点，则次一日之后，股价将随后跌破低点支撑区。投资者可以早一步卖出股票，减少不必要的损失。

③ 股价走势一波比一波高，而ASI却未相对创新高点形成”顶背离“时，应买进。

④ 股价走势一波比一波低，而ASI却未相对创新低点形成”底背离“时，应买进。

⑤ ASI和OBV同样维持”N“字型的波动，并且也以突破或跌破”N“型高、低点，为观察ASI的主要方法。向上爬升的ASI，一旦向下跌破前一次的N型转折点，一律可视为停损卖出的讯号。（参见图6）

⑥ 向下滑落的ASI，一旦向上突破前一次的N型转折点，一律可以视为果断买进的讯号。（参见图7）



 ![ASI](C:\Users\Administrator\Desktop\ASI.jpg)

图6 ASI止损位

 ![ASI2](C:\Users\Administrator\Desktop\ASI2.png)

图7 ASI买进信号

### 4.11 ATR （包含ATR14、ATR6）

#### 4.11.1 均幅指标

ATR，均幅指标（Average True Ranger），是显示市场变化率的指标，主要用于研判买卖时机，属于超买超卖型因子。ATR值的计算，主要通过取一定时间周期内的股价波动幅度的移动平均值。ATR的设计原理依据以下两点，首先，在通常情况下，股价的波动幅度会保持在一定常态下，但是如果有主力资金进出时，股价波幅往往会加剧。其次，在股价横盘整理、波幅减少到极点时，也往往会产生变盘的行情。

#### 4.11.2 指标线

ATR，依据所选时间区间的长度，可以分为ATR14（14日均幅指标）、ATR6（6日均幅指标）。

#### 4.11.3 计算公式

① TR 为（H - L）、（H - CL）和（CL - L）三者绝对值中的最大值。

注：H——今日最高值； L——今日最低值；CL——前一日的收盘价。

② ATR 为TR的N日简单移动平均值。

ATR14，其N值为14；ATR6，其N值为6。

#### 4.11.4 应用法则

主要应用于了解股价的震荡幅度和节奏，在窄幅整理行情中用于寻找突破时机。

① 常态时，波幅围绕均线上下波动；

② 极端行情时，波幅上下幅度剧烈加大；

③ 波幅MAX过高，并且股价上涨过快时，则卖出。

④ 波幅MAX过低，并且真实波幅ATR连创新低时，表明股价已经进入窄幅整理行情中，随时将面临突破。

⑤ 波幅的高低根据不同的个股及个股在不同的阶段由使用者确定。



### 4.12 BBI

#### 4.12.1 指标含义

BBI，多空指数（Bull and Bear Index），是将周期长度不同的移动平均线进行加权计算后得到的综合指标，属于均线型因子。一般选用3、6、12、24日四条平均线。在BBI指标中，近期数据比较多，元气数据利用次数较少，因而是一种变相的加权计算。由于多空指数是一条混合平均线，所以既有短期移动平均线的灵敏，又有明显的中期趋势特征，适用于稳健的投资者。

#### 4.12.2 计算公式

BBI = （3日均价 + 6日均价 + 12日均价 + 24日均价）/ 4

3日均价 = 3日收盘价之和 / 3

注：

① 6、12、24日的均价计算方式参照3日均价的计算方式。

② 由BBI 的连续移动计算，可得到均价多空指标BBI曲线现时价格在BBI之上，表示多方强；反之，表示空方强。

#### 4.12.3 应用法则

① 股价位于BBI 上方，表示多头市场；

② 股价位于BBI下方，表示空头市场；

③ 下跌行情中，若股价跌破BBI曲线，为卖出信号；（参见图8）

④ 上涨行情中，若股价升越BBI曲线，为买入信号；（参加图9）

⑤ 上升回档时，BBI为支持线，可以发挥支撑作用；

⑥ 下跌反弹时，BBI为压力线，可以发挥阻力作用。（参加图10）

 ![BBI图8](C:\Users\Administrator\Desktop\BBI图8.png)

图8 股价跌破BBI曲线

 ![BBI图9](C:\Users\Administrator\Desktop\BBI图9.png)

图9 股价升越BBI曲线

 ![BBI 图10](C:\Users\Administrator\Desktop\BBI 图10.png)

图10 BBI曲线为压力线



### 4.13 BBIC

#### 4.13.1 指标含义

BBIC，属于均线型因子，通过BBI除以收盘价得到。



### 4.14 BearPower

#### 4.14.1 指标含义

BearPower，空头力量，是驱动市场价格下降的力量，与BullPower相对。BearPower为计算Elder因子的中间变量，属于能量型因子。通常情况下，BearPower、BullPower与EMA（指数平滑移动平均线）一起使用。

#### 4.14.2 计算公式

*① BearPower = 目前最低价 - EMA（收盘价，13）*

*② EMA t = Pt * 2 / n + 1 + EMA t - 1 * （1 - 2 / n + 1）*

注： t 为当前时间段，Pt为当前收盘价，EMA（收盘价，13）为13个相同时间单位周期的EMA 相加除以13，其中13为系统默认参数，是可以改变的，而EMA中的参数值收盘价（close）也是可以在属性中更改的。

#### 4.14.3 应用法则

EMA趋势上升，出现以下情况时可以买入：

① BearPower在零点之下，但趋势在上升时；

② 上一个BullPower顶峰点比再上一个BullPower顶峰点更高时，可以买入；

③ BullPower与价格趋势背离后，BullPower在上升时。

EMA趋势下降，出现以下情况是可以卖出：

① BullPower在零点之上，但趋势在下降时；

② 上一个BullPower顶峰点比再上一个BullPower顶峰点更低时；

③ BearPower与价格趋势背离后，BullPower在下降时。



### 4.15 BIAS（包含BIAS5、BIAS10、BIAS20、BIAS60） 

#### 4.15.1 指标含义

BIAS，乖离率，简称Y值，是移动平均原理派生的一项技术指标，表示股价偏离趋势指标占百分比值，属于超买超卖型因子。

#### 4.15.2 指标线

BIAS指标有3条指标线，即BIAS5、BIAS10、BIAS20、BIAS60。

#### 4.15.3 计算公式

BIASn = （收盘价 - 收盘价的n日简单移动均值） / 收盘价的n日简单移动平均 * 100。

#### 4.15.4 应用法则

BIAS，表现个股当日收盘价与移动平均线之间的差距。当股价的正乖离率扩大到一定极限时，表示短期获利越大，则获利回吐的可能性越高；当股价的负乖离扩大到一定极限时，则空头回补的可能性越高。

股价与乖离率究竟达到何种程度的百分比才算是买进或是卖出的时机，不同市场、不同时期、不同周期及不同移动平均线算法所得出的乖离率不同，不能一概而论，要根据偏离的大小及行情的强弱而定。在多头行情中，会出现许多高价，太早卖出会错失一段行情，可于先前高价之正乖离率点卖出；反之，在空头市场时，亦会使负乖离率加大，可于前次低价之负乖离率时买进。



### 4.16 Boll

#### 4.16.1 指标含义

Bull，布林指标（Bollinger Bands），是用于研判股价运动趋势的一种中长期技术分析工具，属于超买超卖型因子。Boll主要利用统计原理，求出股价的标准差及其信赖区间，从而确定股价的波动范围以及未来趋势，利用波带显示股价的安全高低价位，因而也被成为布林带。股价涨跌幅度加大时，带状区变宽；股价涨跌幅度狭小盘整时，带状区则变窄。

#### 4.16.2 指标线

Boll指标线有两条，即BollDown（下轨线）、BollUp（上轨线）。

#### 4.16.3 计算公式

BollUp = 中线 + 偏移值

BollDown = 中线 - 偏移值

#### 4.16.4 应用法则

① Boll利用波带显示股价的安全高低价位；

② 当易变性变小，而波带变窄时，激烈的价格波动有可能买上发生，表示变盘在即；

③ 高低点穿越上轨或下轨，立刻又回到波带内有短期回档或短期反弹发生；

④ 波带开始移动过后，以此方式进入另一波带，这对于找出目标值很有帮助；

⑤ Boll适合跟%BB、WIDTH配合使用。

注：Boll虽然是压力支撑指标，但也具有判断超买超卖的特性和功能，它和ROC、CCI等指标配合使用，可以相互弥补不足之处。当Boll的带状区呈水平方向移动时，可视为处于常态范围。此时，若股价向上穿越上限，则将出现短期回档，是断线卖出信号；若股价向下穿越下限时，则将出现断线反弹，为短线的买入时机。当股价连续穿越上限，表明股价将朝上升方向推进；当股价连续穿越下限，表明股价将下跌。



### 4.17 BR

#### 4.17.1 指标含义

BR，意愿指标，是以昨日收市价为基础，分别于当日最高价、最低价相比，通过一定时期收市价在股价中的地位，反映市场买卖意愿的程度，属于能量型因子。

##### 4.17.2 计算公式

BR = HIGH(n) / LOW(n) * 100

注：n 为26天。

#### 4.17.2 应用法则

① 通常BR ＞ 300为超卖区，需注意股价的回档行情；BR ＜ 50为超卖区，需注意股价的反弹行情。

② 其正常区间在70~150之间，属于盘整行情。从正常区外围至超买、超卖区间，可视为警戒区。

③ 一般BR要与AR配合使用，才能发挥BR的效用。

④当AR、BR均急速上升时，意味着距离股价高峰已近，持股者应获利了结。BR低于AR时，可逢低买进；反之，BR急速上升，而AR盘整或小回时，应逢高出货。

⑤ BR在超过300时，容易引发获利回吐的卖压。

⑥ BR由80-60-40下降至低水平，并且持续较长一段时间时，股价正在酝酿底部的可能性较大。

⑦ BR先在100附近的均衡状态徘徊，而后开始上升，则由此均衡状态内的低点起算，BR上涨一倍时为获利卖出的好机会。

⑧ BR由高档下降一半，此时选择股价回档买进，成功率较高。

⑨ 当BR超过300、400却仍无向下转弯的迹象时，应立刻放弃使用BR指标，改用CR指标。



### 4.18 BullPower

#### 4.18.1 指标含义

Bullpower，多头力道，是计算Elder因子的中间变量。BullPower，与BearPower相对，是驱动市场价格上升的力量，属于能量型因子。

#### 4.18.2 计算公式

BullPower = 目前最高价 - EMA （收盘价 ，13）

EMA t = pt * 2 / n + 1 EMA t - 1 * （1 - 2 / n + 1）

注：① t为当前时间段；

​       ② Pt为当前收盘价；

​       ③ EMA（收盘价，13）为13个相同单位周期的EMA相加，再除以13，其中13为系统默认参数，可以改变。

#### 4.18.3 应用法则

EMA趋势上升，可以买入的情形有：

① 上一个牛市顶峰点比再上一个牛市顶峰点更高时；

② 牛市与价格背离后而熊市在上升时。

EMA趋势在下降，可以卖出的情形有：

① 牛市在零点之上，但趋势在下降时；

② 上一个牛市顶峰点比再上一个牛市顶峰点更低时；

③ 当牛市在零点之下时，最后不要做单。

注：一般情况下，BullPower与BearPower、EMA（指数平滑移动平均线）一起使用。



### 4.19 CCI （包括CCI5、CCI10、CCI20、CCI88）

#### 4.19.1 指标含义

CCI，顺势指标（Commodity Channel Index），专门测量股价是否超出常态分布范围，属于超买超卖型因子。当股票进入强势上涨阶段的时候，CCI提示的买入信号往往是股票已经开始启动，涨速最快、上升幅度最大的主升浪行情，这阶段的获利也是最丰厚的。

#### 4.19.2 指标线

CCI的指标线有三条，即CCI5、CCI10、CCI20、CCI88指标线。

#### 4.19.3 计算公式

① TYP = （最高价 + 最低价 + 收盘价） / 3

② CCI = （TYP - TYP的N日简单移动平均）/ （0.015 * TYP的N日平均绝对方差）

#### 4.19.4 应用法则

① CCI为正值时，视为多头市场；为负值时，视为空头市场。

② 常态行情时，CCI波动于±100之间；强势行情时，CCI会大于100；弱势行情时，CCI会小于-100.

③ CCI由下往上突破+100天线时，为买进时机，直到CCI从+100天线之上，由上往下跌破天线时，再卖出

④ CCI由上往下跌破-100底线时，为卖出做空时机，直到CCI从-100 地线之下，由下往上突破底线时，再买入。值得注意的是，中国股市目前只能做多，不能做空。因此，这里的做空只是一种抛售已持有的股票的一种被动做空方式。

⑤ CCI具有良好的避险功能，在弱势中，如果股价趋势没有真正转变，CCI指标往往长时间徘徊在+100之下，这是投资者不要贪图反弹的小利，而是要静观其变，耐心空仓等待。



### 4.20 ChaikinOscillator

#### 4.20.1 指标含义

Chaikin Oscillator，佳庆指标，该指标基于AD曲线的指数移动均线而计算得到，属于趋势型因子。Chaikin Oscillator是一种成交量指标，从A/D衍生而来。

Chaikin Oscillator的设计原理：在价格的波动趋势中，成交量分析有助于掌握股价本质上的强弱度。成交量与股价相**背离**的现象，经常是确认**反转讯号**的唯一线索。因而，为了将市场的内在动能真实地表现在分析图表上，就需要将**成交量**列入考虑的范围。Chaikin Oscillator以**当日收盘价**和**当日开盘价**比较，以侦测**量价背离**。如果收盘价高于开盘价，则开盘价距收盘价之间的上涨幅度，以正值百分比表示，并乘以当日成交量；如果收盘价低于开盘价，则开盘价距收盘价之间的下跌幅度，以负值百分比表示，再乘以当日成交量。

#### 4.20.2 计算公式

①  ![公式png](C:\Users\Administrator\Desktop\API 说明文档 图片\公式png.png)

② Chikin ＝ A/D的（n）expma - A/D的（m）expma

注：C —— 当日收盘价；L——当日最低价；H——当日最高价；V——当日成家量

#### 4.20.3 应用法则

① Chaikin Oscillator与股价相背离时，可视为反转讯号。（特别是其他搭配运用的指标群，正处于超买或者超卖的水平时。）

② Chaikin Oscillator本身具有超买超卖的作用，但是，超买和超卖的界限位置因个股而定。

③ Chaikin Oscillator由负值向上穿越0轴时，为买进讯号；由正值向下穿越0轴时，为卖出讯号。但是需要注意的是，前者必须位于90天移动平均线之上， 后者必须位于之下，方可视为有效。

注：

① 以中间价为基准，如果收盘价高于当日中间价，则当日成交量为正值。收盘价越接近当日最高价，其多头力道越强。如果收盘价低于当日中间价，则当日成交量为负值。收盘价越接近当日最低价，其空头力道越强。

② 一波健全的上升趋势，必须包含强劲的多头力道。

③ Chaikin Oscillator一般与21天的Envelope指标、超买超卖指标、佳庆指标组成一个指标群，以降低假讯号的发生概率。



### 4.21 ChaikinVolatility

#### 4.21.1 指标含义

ChaikinVolatility，佳庆离散指标（Chaikin Volatility，简称CVLT，VCI，CV），又称“佳庆变异率指数”，是通过测量一段时间内价格幅度平均值的变化来反映价格的离散程度，通常与移动平均线（如：简单移动平均线、EMA、WMA）、Envelope配合使用。Chaikin Volatility，属于趋势型因子。

#### 4.21.2 计算公式

① 步骤一：计算n日的Range

Range = High - Low = 价差指数平滑移动平均

REMAt = REMA(t-1) + 2 / (n +1) * [ REMAt - REMA(t-1) ]

② 步骤二：计算n日移动平均的变动率

Chaikin Volatility = [ REMA(t) - REMA(t-n) ] / REMA(t-n)

注：

① 价差指数平滑移动平均是将一段时间最高价与最低价之差进行指数平滑移动平均（EMA）所得出的数值。

② 描述价格的波动程度的状况有两种：一种认为当股价向上时波动程度随之上升，此种描述是认为价格上升时经常伴随着成交量放大，这表示此过程将吸引更多的市场参与者加入，而更多人参与交易则隐含着波动程度的放大。另一种状况则是认为，观察短期的价格走势，则波动的讯杂干扰会较长期来得大。

#### 4.21.3 应用法则

① 当价格上涨形态被破坏，病进入区间盘整状态，此时CV曲线处于顶部（高水平位置）；

② 区间盘整或区间被突破时，CV曲线通常处于底部（低水平位置）；

③ 汇率上涨时，CV指标的数值将随之上升；

④ 当汇率将要到达顶部时，会出现突然加速上升的现象；

⑤ 当市场渐渐无力时，反转行情的可能性增高，会出现急速下降的现象。



### *4.22 ChandeSD*

#### 4.22.1 指标含义

ChandeSD，计算CMO因子的中间变量，SD是今日收盘价与昨日收盘价（下跌日）差值的绝对值加总。若当日上涨，则增加值为0。属于超买超卖型因子。



### *4.23* *ChandeSU*

#### 4.23.1 指标含义

ChandeSU，计算CMO因子的中间变量，SU是今日收盘价与昨日收盘价（上涨日）差值加总。若当日下跌，则增加值为0。属于超买超卖型因子。



### 4.24 CMO

#### 4.24.1 指标含义

CMO，钱德动量摆动指标（Chande Momentum Osciliator），与其他动量指标摆动指标如相对强弱指标（RSI）和随机指标（KDJ）不同，钱德动量指标在计算公式的分子中采用上涨日和下跌日的数据。属于超买超卖型因子。

#### 4.24.2 计算公式

CMO = （Su - Sd) × 100 / (Su + Sd)

注：

① Su——当日收盘价与前一日收盘价（上涨日）差值加总，若当日下跌，则增加值为0。

② Sd——当日收盘价与前一日收盘价（下跌日）差值的绝对值加总，若当日上涨，则增加值为0。

#### 4.24.3 应用法则

① CMO作为一个通过规则，把超买水平定量在+50以上，把超卖水平定量在-50以下。

② CMO的绝对值越高，则趋势越强。较低的CMO绝对值（0附近）表示标的证券在水平方向波动。在50+，上涨日的动量是下跌日动量的3倍；同样，在-50，下跌日的动量是上涨日动量的3倍。这些水平值可与RS指标中的70/30相对应。

③ 可以通过用CMO的绝对值较高时仅根据趋势跟踪指标来操作；当CMO的绝对值较低时，转而采用交易范围指标。



### 4.25 CoppockCurve

#### 4.25.1 指标含义

CoppockCurve，估波指标（Coppock Curve），又称“估波曲线”，该指标通过计算月度价格的变化速率的加权平均值来测量市场的动量，属于长线指标，这里我们改为日间的指标。CoppockCurve，主要用于判断牛市的到来，而且该指标用于研判大盘指数较为可靠，一般较少用于个股；而且该指标只能产生买进讯号，卖出讯号需要寻求其他指标来辅助。该指标属于趋势型因子。

#### 4.25.2 计算公式

R(n1) = 100 ×（当日收盘价 － 前n1日收盘价）÷ 前n1日收盘价

R(n2) = 100 ×（当日收盘价 － 前n2日收盘价）÷ 前n2日收盘价

RC(n1, n2) =R(n1)R(n2)

Coppo(n1, n2, n3) = WMA [ RC(n1, n2), n3]　(RC的加权平均值，权重n3)

注：两个周期参数n1、n2，胶圈平均数n3。

#### 4.25.3 应用法则

① 估波指标适合在指数的月线图表中分析；

② 当估波曲线从零以下向上穿越零线，预示牛市来临，是中期买入信号；

③ 估波指标不适宜寻找卖出时机，应结合其它指标来进行分析；

④ 估波指标与价格的背离，也是买卖信号；

⑤ 估波指标在时机运用过程中，可结合KDJ指标、MACD指标、均线等综合运用。

注：估波指标的周期参数一般设置为11、14，加权平均参数为10，也可以结合指标的平均线进行分析。



### 4.26 CR20

#### 4.26.1 指标含义

CR20，20日带状能量线，以上一个计算周期（这里为20日）的中间价比较当前周期的最高价、最低价，计算出一段时期内股价的“强弱”。该指标能够测量价格动量的潜能，又能测量人气的热度，同时还能显示压力带和支撑带，可以补充情绪带指标的不足，属于能量型因子。

#### 4.26.2 计算公式

CR指标的计算公式和BR相同，只是把公式中昨日的收盘价改成昨日的中间价。CR可以辅助AR、BR的不足。

CR(n) = n日内（H - PM）之和 / n日内（PM - L）之和

注：

① H——最高价；L——最低价；PM——昨日的中间价，中间价为最高价、最低价与开盘价三者的平均值。

② CR以昨日的中间价为基础，理论上比中间价位高的从前位其能量围墙，反之则弱。CR就是通过计算一段时期内“弱分之强”的数值，从而分析其在价格波动中的作用，来预示股价涨跌的幅度和时间。

③ CR在应用上，一般比较接近BR，当CR低于100时，一般情况下买进的风险不大。

#### 4.26.3 应用法则

以图11为例：

 ![CR20](C:\Users\Administrator\Desktop\API 说明文档 图片\CR20.png)

图11CR指标线

① CR平均线周期由长至短分成A、B、C、D四条，A、B两条线所夹成的区域称为“副地震带”，C、D两条线所夹成的区域称为“主地震带”。

② 当CR由下往上欲穿越A、B两条线所夹成的“副地震带”区域时，股价相对将遭遇次级压力干扰；当CR欲由上往下贯穿该区域时，股价相对将遭遇次级支撑干扰。

③ 当CR由下往上欲穿越C、D两线所夹成的“主地震带”区域时，股价相对将遭遇强大压力干扰；当CR欲由上往下贯穿该区域时，股价相对将遭遇强大支撑干扰。

④ CR相对股价也会产生背离现象，特别是在股价的高价区。

⑤ CR跌至A、B、C、D四条线的下方，再度由低点向上爬升至160%时，为短线获利卖出时机。

⑥ CR下跌至40以下时，股价形成底部的机会相当高。

⑦ CR高于300~400之间时，股价很容易向下反转。

⑧ 当A、B、C、D四条线在CR前方若干天的地方，几乎同时交叉在一点时，那一点的时间未知是一个股价起涨点或者起跌点。这个讯号一旦出现，则其相对成功几率非常高。



### 4.27 DBCD

#### 4.27.1 指标含义

DBCD，异同离差乖离率，其优点在于能够保持指标的紧密同步，并且线条光滑，信号明确，能够有效的过滤掉伪信号。属于超买超卖型因子。

#### 4.27.2 计算公式

① 步骤一：计算乖离率BIAS;

② 步骤二：计算不同日的乖离率之间的离差；

③ 步骤三：对离差进行指数平滑处理。

#### 4.27.3 应用原则

 当指标出现脉冲信号时，为阶段性底部即将形成的信号。当出现双针信号或连续的多针信号时，通常表明底部已经确立，上涨即将展开。当底部信号已发出，但受突发因素的影响导致股价下跌（通常跌幅 10%左右），在数周后底部信号再度出现时，表明底部 已经确立，股价处于上升途中。

注：

① 对前期涨幅巨大的庄股（从周线上来看）出现回调时使用该指标时需慎重。虽 然该股已大幅下挫，但是其股价与主力成本相距较远，底部信号的发出仅能表明有小幅 反弹或平台整理，无法改变股票下跌趋势。此时介入有着巨大的风险。 

② 由于个股在除权后股价往往出现较大价差，极易造成底部信号的出现，形成指 标失真，所以要先复权后再使用。 



### 4.28 DDI（包含DIF、DIZ） 

#### 4.28.1 指标含义

DDI，方向标准离差指数，观察一段时间内股价相对于前一天向上波动和向下波动的比例，并对其进行移动平均分析，DDI指标倾向于显示一种长波段趋势的方向改变。通过分心DDI柱状线，可以判断是买入信号还是卖出信号，属于趋势型因子。DDI、DIF、DIZ，三者均属于趋势型因子。

#### 4.28.2 计算公式

① TR = （最高价 - 昨日最高价）的绝对值与（最低价 - 昨日最低价）的绝对值两者之间较大者；

② 如果（最高价 + 最低价）≤ （昨日最高价 + 昨日最低价），DMZ = 0；

如果（最高价 +  最低价）＞ （昨日最高价 + 昨日最低价），DMZ = （最高价 - 昨日最高价）的绝对值与（最低价 - 昨日最低价）的绝对值中较大者。

③ 如果（最高价 + 最低价）≥ （昨日最高价 + 昨日最低价），DMF = 0，

如果（最高价 + 最低价）＞ （昨日最高价 + 昨日最低价），DMZ = （最高价 - 昨日最低价）的绝对值与（最低价 - 昨日最低价）的绝对值中较大者。

④ DIZ = n个周期的DMZ的和 / （n个周期DMZ的和 + n个周期DMF的和）

⑤ DIF = n个周期DMF的和 / （n个周期DMF的和 + n个周期DMZ的和）

⑥ DDI = DIZ - DIF

⑦ ADDI = DDI 在一定周期内的加权平均

⑧ AD = ADDI在一定周期内的简单移动平均

#### 4.28.3 应用法则

① 分析DDI柱状线，由红变绿（正变负），卖出信号；由绿变红，买入信号。

② ADDI与AD的交叉与背离情况。

③ 与MACD结合使用：MACD指标对股价趋势变化的敏感程度领先于DDI指标，MACD总是领先于DDI指标先翻红或先翻绿。



### 4.29 DMI（包含ADX、ADRX、minusDI、plusDI）

#### 4.29.1 指标含义

DMI，下降指标是技术大师维尔德发明的一套技术分析工具。其基本原理是探求价格在上升及下跌过程中的均衡，即供需关系通过价格的变化由紧张而达成和谐，属于趋势型因子。下降指标在生成的过程中包含了每日的高低波动的浮动因素，以此来分析未来的走势。

#### 4.29.2 指标线

DMI包含四条指标线：上升动向指标（plusDI，或记作+DI）；下降动向指标（minusDI，或记作-DI）；平均动向指数ADX；缓动线ADRX。

注：DMI在应用时，参数N取14最为合适。

#### 4.29.3 应用法则

① +DI、-DI、ADX、ADXR都在0 ~ 100区间波动（正负号仅表示方向，不表示正负值）。

② +DI曲线在-DI曲线上方，表示上升动向强于下降动向，所以+DI曲线上升并穿过-DI曲线是买入信号。当ADX止跌回升，则涨势更强。若ADX升到某一水平，掉头回落，则显示往后纵使上升，升势亦会放缓，且维持的时间不会太久便会转为下跌，直到ADX再掉头转生为止。（参见图12）

 ![DMI的买入信号](C:\Users\Administrator\Desktop\API 说明文档 图片\DMI的买入信号.png)

图12

③ -DI曲线在+DI曲线上方，表示下降动向强于上升动向，所以-DI曲线上升并穿过+DI曲线是卖出信号。若ADX相声攀升，便会出现较急跌势，直至ADX见顶回落，才确实底部的出现，往后的跌势亦较缓，并且出现反弹回升的迹象。（参见图13）

 ![DMI的卖出信号](C:\Users\Administrator\Desktop\API 说明文档 图片\DMI的卖出信号.png)

图13

④ ADX曲线有重要技术含义的上下拐点在70以上、20以下区间。当股价见顶时，ADX会随后见顶，此时ADX在70左右，故ADX的功用是辅助判别涨势或跌势的反转讯号。

⑤ 当+DI和-DI相交叉，出现了买卖的讯号，随后ADX与ADRX相交，便是最后一个买卖的机会。为消除技术骗线的影响，可利用ADRX曲线，其余ADX曲线相交是对判断的一种确认信号，其作用在于提醒投资者采取最后的即时买入或卖出的行动，随后而来的升势或跌势将会较急。

⑥ ADX脱离20 ~ 30之间往上爬升时，无论当时的价格正往上涨还是往下跌，都可以认定将产生一段有相当幅度的行情。

⑦ ADX位于+DI与-DI的下方，特别在20以下时，代表股价已经陷入泥沼，处于沉闷的整理期，此时，应退出市场观望。

⑧ ADX曲线上升，表示当前运行着一种强或者较强的走势（视为曲线陡度）：若+DI在上，它为上升势；若-DI在上，它为下降势。ADX一旦高于50以上，忽然转弯向下反折，此时，不论当时的价格正往上涨或者往下跌，都代表行情即将反转。（参见图14）

 ![DMI的ADX指标线](C:\Users\Administrator\Desktop\API 说明文档 图片\DMI的ADX指标线.png)

图14

⑨ ADX曲线由上升转为下降，意味着之前运行着的趋势已经开始转变。若之前股价运行的是上升势，则调整可先判断为上升回档；若之前股价运行的是下降势，则调整可先判断为下跌反弹。调整结束的信号是ADX曲线由下降转为上升，而调整突破的方向则由+DI与-DI的关系决定。如果调整突破的方向与调整前的一致，则是回档或反弹结束的信号，即上升势仍为上升势，下跌势仍为下跌势。如果认为调整突破的方向与调整前的相反，则确认为市场趋势的逆转。

总之，由以上分析可得：ADX曲线的上拐点和下拐点也是短线操作的买或卖的信号。若确认ADX曲线的下拐点为市场趋势逆转信号，则是中长线操作的买或卖的信号。如果ADX曲线呈现横向移动，则+DI与-DI亦绞合一起，表示此间为无趋势的行情。

### *4.29 DownRVI*

#### 4.29.1 指标含义

计算RVI因子的中间变量。属于超买超卖型因子。



### 4.30 Elder

#### 4.30.1 指标含义

Elder，艾达透视指标（Elder-ray Index），交易者可以经由该指标，观察市场表面之下的多头与空头力道。属于能量型因子。艾达透视指标的设计基于以下原则：

① 价格是以行动表达的价值共识；

② 移动平均代表价值的平均共识；

③ 每支长条图的最高价，代表多头在该时段内的最大力道；

④ 每支长条图的最低价，代表空头在该时段内的最大力道；

⑤ 多头力道是多头最大力量与价值平均共识之间的差值；

⑥ 空头力道是空头最大力量与价值平均共识之间的差值。

#### 4.30.2 计算公式

艾达透视指标结合了**顺势指标**与**摆荡指标**的最佳特性。其中，指数移动平均是**顺势指标**，“**多头力道**”与“**空头力道**”是**摆荡指标**的成份。在指标的设定方面，可以将电脑荧幕（或绘图纸）分割为三个水平的视窗，最上侧的视窗绘制长条图与指数移动平均(EMA)；中间的视窗绘制多头力道；下侧绘制空头力道。

指标的构建分为四个步骤，如图12所示：

 ![艾达透视指标](C:\Users\Administrator\Desktop\API 说明文档 图片\艾达透视指标.jpg)

图12 艾达透视指标图

① 步骤一：在最上侧的视窗绘制长条图。

② 步骤二：在同一个视窗绘制收盘价的EMA，可以采用13天的EMA。

​                    多头力道 = 最高价 － EMA空头力道 = 最低价 － EMA。 　

③ 根据前述公式计算多头力道，在中间的视窗绘制它的柱状图。多头力道是当天最高价减去当天的EMA，在一般的情况下，最高价大于EMA，多头力道为正值，柱状图位在零线的上侧，在急跌的行情中，最高价可能小于EMA，多头力道为负值，柱状图位在零线下侧。

④ 计算空头力道。在最下方的视窗绘制它的柱状图，空头力道是当天最低价减去当天的EMA。在一般的情况下，最低价小于EMA，空头力道为负值，柱状图位在零线的下侧。在急涨的行情中，最低价可能大于EMA[空头力道为正值，柱状图位在零线上侧。

​                  多头力道 = 长条图高价 － 13天EMA 空头力道 = 长条图低价 － 13天EMA 　

在一般的走势中，多头力道为正值，空头力道为负值。多头力道柱状图愈高，代表多头的力道愈强；空头力道柱状图愈深，代表空头的力道愈强。当多头力道转为负值，显[空头的力道完全凌驾多头之上。当空头力道转为正值，显示多头的力道完全凌驾空头之上。

#### 4.30.3 应用法则

##### 4.31.3.1 买进与卖出

① 买进的两个基本条件：

趋势向上（辨识工具为日线图的EMA或周线图的顺势指标）；

空头力道为负值而处于上升状态。

②买进的两个非必要的条件：

多头力道的最近一个峰位高于前一个峰位；

空头力道形成多头的背离。

##### 4.31.3.2 放空与回补

① 放空的两个基本条件：

趋势向下（辨识工具为日线图的EMA或周线图的顺势指标）；

多头力道为正值而处于下降状态。

② 放空的两个非必要条件：

空头力道的最近一个谷底低于前一个谷底；

多头力道形成空头的背离。



### 4.32 EMA（包含EMA12、EMA26）

#### 4.32.1 指标含义

EMA，指数移动均线（Exponential moving average），具备了KDJ指标与MACD指标的“金叉”与“死叉”的功能，同时，避免了平均线不能及时对价格脱离均线差扩大做出反应的问题。因而，该指标可以为个股的抄底和逃顶提供较好的点位，是投资者采用中短线决策的好帮手。

#### 4.32.2 指标线

EMA包含两条指标线，即EMA12、EMA26。

#### 4.32.3 计算公式

EMA(X,N) = 2 * X / (N + 1) + (N - 1) / (N + 1) * 昨日的指数收盘平均值

注：

① EMA(X,N)——X的N日指数平滑移动平均；

② X——当日收盘价；

③ N——天数。

#### 4.32.3 应用法则

① EXPMA指标由EXPMA1(白线)和EXPMA2(黄线)组成，当白线由下往上穿越黄线时，股价随后通常会不断上升，那么这两根线形成金叉之日便是买入良机。

② 当一只个股的股价远离白线后，该股的股价随后很快便会回落，然后再沿着白线上移，可见白线是一大支撑点。

③ 同理，当白线由上往下击穿黄线时，股价往往已经发生转势，日后将会以下跌为主，则这两根线的交叉之日便是卖出时机。



### 4.33 EMV（包含EMV6、EMV14）

#### 4.33.1 指标含义

EMV，简易波动指标（Ease of Movement Value），EMV将价格与成交量的变化结合成一个波动指标来反映股价或指数的变动状况，由于股价的变化和成交量的变化都可以引发该指标数值的变动，EMV实际上也是一个量价合成指标。该指标的设计原理为，价格在上升趋势的保持过程中将不会耗用太多的能量，仅当趋势发生转折时，成交量才会放大。该股票属于趋势型因子。

#### 4.33.2 指标线

EMV的指标线有两条，即EMV6、EMV14。

 #### 4.33.3 计算公式

① A = （今日最高价 - 今日最低价）/ 2

② B = （前一日最低价 + 前一日最低价）/ 2

③ C = （今天最高价 - 今天最低价）

④ EM = （A - B）* C / 今日成交额

⑤ EMV = 累计n日的EM值

注：EMV指标往往还附加了另一个辅助指标。即EMVMA，这一指标其实就是对EMV值的一次算数平均，是计算EMV的M日移动平均线。此外，在技术分析软件中，WMV指标的参数N=14，M=9。

#### 4.33.4 应用法则

① EMV值上升代表放量上升，在价格的上升阶段是正常的信号；EMV值下降代表缩量下跌，在价格的下跌阶段（尚未完成时），也是一个正常的信号。

② 当EMV由下往上穿越0轴时，视为中期买进信号；当EMV由上往下穿越0轴时，视为中期卖出信号。

③ 当EMV指标的平均线跨越0轴为讯号，所产生的交易成果比较令人满意。

④ 当DMI中的ADX低于±DI时或ADXR出现“指标失效”讯号时，该指标失去效用，应立即停止使用EMV指标。

⑤ 在分析软件中，辅助指标WMVMA与WMV之间的交叉情况仍然值得注意。

⑥ 指标同样强调形态，而当价格到达头部时，指标先于价格作出下跌反应。

注：WMV指标反映的是价格运行的全过程中成交量的动态变化情况，因此，指标更具有对价格中长期走势的预警性，须长期使用EMV，才能获得最佳投资效果。



### 4.34 Hurst

#### 4.34.1 指标含义

Hurst，赫斯特指数（Hurst exponent）。是由英国水文专家H．E．Hurst提出了用重标极差(R/S)分析方法来建立赫斯特指数(H)，作为判断时间序列数据遵从随机游走还是有偏的随机游走过程的指标。属于趋势型因子。

#### 4.34.2 计算公式

##### 4.34.2.1 赫斯特指数的设计原理

设**Xi** = **X1**,…,**Xn**为一时间序列的**n**个连续值，将取对数并进行一次差分后的数据划分为长度为**H**的相邻的子区间**A**，即**A*H=n**。

##### 4.34.2.2 公式

① 每个子区间的均值为：

Xm = (X1 + … + Xh) / H

② 标准差为：

 ![赫斯特指数 标准差](C:\Users\Administrator\Desktop\API 说明文档 图片\赫斯特指数 标准差.png)

③ 均值的累计横距（XKA）为：

 ![赫斯特指数 横距](C:\Users\Administrator\Desktop\API 说明文档 图片\赫斯特指数 横距.png)

④ 组内极差为：

　Rh = max(Xr,A)-mix(Xr,A)

⑤ Hurst指数（H）为：

 ![赫斯特指数 H](C:\Users\Administrator\Desktop\API 说明文档 图片\赫斯特指数 H.png)

⑥ Hurst推出的关系为：

 ![赫斯特指数 推导公式](C:\Users\Administrator\Desktop\API 说明文档 图片\赫斯特指数 推导公式.png)

注：c为常数；n为观察值的个数；H为Hurst指数。

#### 4.34.3 应用法则

① 如果H = 0.5，表明时间序列可以用**随机游走**来描述；

② 如果0.5 < H ≤ 1，表明黑噪声（持续性），即暗示**长期记忆**的时间序列；

③ 如果0 ≤ H < 0.5，表明粉红噪声（反持续性），即**均值回复**过程。

总之，只要H ≠ 0.5，就可以用**有偏的布朗运动**（分形布朗运动）来描述该时间序列数据。



### 4.35 JDQS20

#### 3.35.1 指标含义

JDQS20，阶段强势指标，该指标计算一定周期n日内，大盘下跌时，个股上涨的比例。属于能量型因子。

#### 4.35.2 计算公式

D = A / B

注：

① A：n天中大盘收阴线而个股收阳线的天数；

② B：n天中大盘收阴线的天数；

③ D：JDQS20的强弱程度

#### 4.35.3 应用法则

D值越大，则股票在这一阶段中走势越强。



### 4.36 KDJ（包含KDJ_D、KDJ_J、KDJ_K）

#### 4.36.1 指标含义

随机指标，它综合了动量观念、强弱指标及移动平均线的优点，用来度量股价脱离价格正常范围的变异程度。属于超买超卖型因子。

#### 4.36.2 指标线

KDJ包含三条指标线，即KDJ_D、KDJ_J、KDJ_K。

#### 4.36.3 计算公式

① RSV = （收盘价 - n日内最低价的最低值）/（n日内最高价的最高值 - n日内最低价的最低值）* 100

② K = RSV的M1日累计平均；

③ D = K的M2日累积平均；

④ J = 3 * K - 2 * D

注：n 为9天；M1为3天；M2为3天。

#### 4.36.4 应用法则

① K值高于80超买区时，短期股价容易向下回档；K值低于20超卖区时，短期股价容易向上反弹。

② K值在20左右水平，从D值右方向上交叉D值时，为短期买进讯号。

③ K值在80左右水平，从D值右方向下交叉D值时，为短期卖出讯号。

④ J值 ＞ 100时，股价容易形成短期头部；J值 ＜ 0时，股价容易形成短期底部。

⑤ KDJ波动于50左右的任何信号，其作用不大。

⑥ 背离现象——价格创新高或新低，而KD未有此现象，亦为反转的重要前兆。

⑦ K值形成一底比一底高的现象，并且在20左右的低水平，由下往上联系两次交叉D值时，股价涨幅会较大。

⑧ K值形成一顶比一顶低的现象，并且在20左右的高水平，由上往下连续两次交叉D值时，股价跌幅会较大。

⑨ J值在短期内连续三次上穿0线，僵尸重要买入信号；J值在短期内连续三次跌穿100线，僵尸重要卖出信号。



### 4.37 KlingerOscillator

#### 4.37.1 指标含义

KlingerOscillator，成交量摆动指标，可用于观察短期和长期股票资金的流入和流出的情况，其主要用途是确认股票价格趋势的方向和强度。因为该指标在决定长期资金流量趋势的同时保持了对于短期资金流量的敏感性，因而可以用于预测短期价格拐点。该指标属于成交量型因子。

#### 4.37.2 计算方法

① 步骤一：P(n) = (C + H + L) / 3

若 P(n) ＞ P(n - 1)，则V(n)为正值；反之，V为负值。

② 步骤二：计算V(34)、V(55)的指数移动平均值

③ 步骤三：KlingerOscillator为**V(34)、V(55)的指数移动平均值**两者之差。

注：

① P(n)——股票在每个交易日的平均价格；C——收盘价；H——最高价；L——最低价。

② V(34)—— 第34天股票成交量经正负判断后的值；V(55)——第55天的股票成交量经正负判断后的值。

③ 为了更好的观察这个指标的趋势，还可以计算这个指标的13天移动平均值。

#### 4.37.3 应用法则

① 如果股价是上升趋势，KO的摆动范围靠上（大于0的方向）；如果是下降趋势，KO的摆动范围靠下（小于0的方向）。

② 如果用它来判断股价趋势的强弱就要看这个指标与股票价格之间有没有背离现象出现。股票价格下跌，KO指标出现多头背离，那么交易方向为买入；股票价格上涨，KO指标出现空头背离，那么就要伺机做空股票。

#### 4.37.4 相关指标

累积克林格成交量摆动指标Cumulative Klinger Oscillator是一个与累积能量线OBV相似的指标，它是利用根据日间股票平均价格的变动而对成交量累积而成，而在累积能量线OBV中用的是日间股票的收盘价的变动来作为成交量累积的标准。相对来说，累积克林格成交量摆动指标比KO指标更适合用于判断股票价格趋势的方向。



### *4.38 MA10Close*

#### 4.38.1 指标含义

MA10Close，均线价格比。由于股票的成交价格有响起均线回归的趋势，计算均线价格比可以预测股票在未来周期的运动趋势。属于均线型因子。



### *4.39 MA10Regress（包括MA10RegressCoeff12、MA10RegressCoeff6）*

#### 4.39.1 指标含义

MA10RegressCoeffn，10日价格平均线n日线性回归系数。属于趋势型因子。

#### 4.39.2 指标线

MA10RegressCoeffn有两条指标线：10日价格平均线6日线性回归系数，即MA10RegressCoeff6；10价格平均线12日线性回归系数，即MA10RegressCoeff12。



### 4.40 MassIndex

#### 4.40.1 指标含义

MassIndex，梅斯线（Mass Index），该指标是Donald Dorsey累积股价波幅宽度之后所设计的震荡曲线，其主要用于寻找飙涨股或者极度弱势股的重要趋势反转点。属于能量型因子。

#### 4.40.2 计算公式

 ① AHL = DIF的9天指数平均数；

② BHL = AHL的9天指数平均数；

③  ![mass指标 ](C:\Users\Administrator\Desktop\API 说明文档 图片\mass指标 .jpg)

注：Mass Index一般将参数设为25天，可视需要将周期缩短至12天。同时，参考Mass Index指标时，须同时观察K线走势，并且在K线图上绘制一条股价的9天移动平均线。

#### 4.40.3 应用原则

① Mass Index向上穿越27，随后又掉头跌落26.5。当时，如果股价的9天移动平均线，正处于上升状态，代表多头行情即将反转下跌。

② Mass Index向上穿越27，随后又掉头跌落26.5。当时，如果股价的9天移动平均线，正处于下跌状态，代表空头行情即将反转上涨。

③ Mass Index低于25的股票，一般较不具投资利润。

注：由于Mass Index比较敏感，因此有必要对其参数进行修正。将Mass Index参数的默认值由25改为60，搭配的移动平均线由9改为25，可过滤掉一些不必要的信号，提供准确性。



### 4.41 MFI（包含MoneyFlow20）

#### 4.41.1 指标含义

MFI，资金流量指标（Money Flow Index），该指标根据**成交量**来计测市场供需关系和买卖力道。MoneyFlow20，为其20日资金流量，用收盘价、最高价及最低价的均值乘以当日成交量即可得到该交易日的资金流量。属于成交量型因子。

#### 4.41.2 计算公式

① 步骤一：选取长度为20的计算期以及典型价格（包括20天收盘价中最高价、最低价和14天最后一天收盘价的算数平均值。）

② 步骤二：计算货币流量

货币流量 = 典型价格 * 20内的总交易量

注：如果后20天的典型价格高于前20天的典型价格，改日的货币流量就去正值；反之，去负值；若相等，则取**0**。

③ 步骤三：定义该交易日后20个交易日内的正货币流量（PMF）总和为正货币流量之和，该交易日后20个交易日内的负货币流量（NMF）总和为负货币流量之和，这类似于OBV的计算方法。正负货币流量和之比简称为**货币比**（PMF / NMF）。

④ MoneyFlow20 = 100 - [100 / (1 + PMF / NMF)]

#### 4.41.3 应用法则

 显示超买超卖是MoneyFlow20最基本的功能。

① 当MoneyFlow20 ＞ 80时为超买，当其回头向下跌破80时，为短线卖出时机。

② 当MoneyFlow20 ＜ 20时为超卖，当其回头向上突破20时，为短线买进时机。

③ 当MoneyFlow20 ＞ 80时，而产生背离现象时，视为卖出信号。

④ 当MoneyFlow20 ＜ 20时，而产生背离现象时，视为买进信号。



### 4.42 MTM（包含MTMMA）

#### 4.42.1 指标定义

MTM，动量指标（Momentom Index），动量指数以分析股价波动的速度为目的，研究股价涨跌速度的变化（包括加速、减速、惯性作用）以及股价由静到动或由动转静现象的指标。该指标属于趋势型因子。

#### 4.42.2 指标线

MTM的10日均值线为MTMMA。

#### 4.42.2 计算公式

① MTM = 当日收盘价 - N日前收盘价

② MTMMA = MTM的M日移动平均

注：N间隔天数一般设为12天；M是求移动平均的天数，一般取6.

#### 4.42.3 应用法则

① MTM从下向上突破MTMMA，为短期买入信号；

② MTM从上向下跌破MTMMA，为短期卖出信号。

③ 股价在上涨行情中创出新高点，而MTM未能配合上升，出现背离，为卖出信号；股价在下跌行情中走出新低点，而MTM未能配合下降，出现背离，为买入信号。

④ 若股价与MTM在低位同步上升，显示短期将有反弹行情；若股价与MTM在高位同步下降，则显示短期可能出现股价回落。



### 4.43 NVI 

#### 4.43.1 指标含义

NVI，负成交量指标（Negative Volume Index），该指标的主要作用是辨别目前市场行情是处于多头行情还是空头行情，并追踪市场资金流向。该指标基于的理论观点：当日的市况如果价跌量缩时，表示后市行情仍然有良好表现的机会。该指标属于能量型因子。

#### 4.43.2 计算公式

NVI = NV + [CLS - CLS(n)] + CLS(n) * NV

注：第一次计算时，前一日的NVI一律以100代替，并计算NVI的N天移动平均线。其中，参数N设定为72。

#### 4.43.3 应用法则

① NVI指标位于其N天移动平均线之上时，表示目前处于多头市场；

② NVI指标由下往上穿越其N天移动平均线，代表长期买进讯号。

③ NVI指标位于其N天移动平均线之下时，表示目前处于空头市场。

④ NVI指标由上往下穿越其N天移动平均线时，代表长期卖出讯号。

⑤ NVI指标与PVI指标分别向上穿越其N天移动平均线时，视为大多头讯号。



### 4.44 OBV

#### 4.44.1 指标含义

OBV，能量潮指标（On Balance Volume，OBV），以股市的成交量变化来衡量股市的推动力，从而研判股价的走势。通常股价上升所需的成交量总是较大；下跌时，则成交量可能放大，也可能较小。价格升降而成交量不相应升降，则市场价格的变动难以为继。该指标属于成交量型因子。

#### 4.44.2 指标线

OBV有两条指标线：6日能量潮指标线，即OBV6；20日能量潮指标，即OBV20。

#### 4.44.3 计算公式

① 当今日收盘价高于昨日收盘价时，今日的成交量列为**正值**；当今日收盘价低于昨日收盘价时，则今日的成交量列为**负值**，选定周期内的正副职成交量累计相加，即为OBV数值。将这些数值标于图上并相连，即得到OBV线。

② 由于OBV的计算方法过于简单化，所以容易受到偶然因素的影响，为了提高OBV的准确性，可以采取**多空比率净额法**对其进行修正。

多空比率净额= [（收盘价 － 最低价）－（最高价 - 收盘价）]  ÷ （ 最高价－最低价）× V

#### 4.44.4 应用法则

① 当股价上升而OBV线下降，表示买盘无力，股价可能会回跌。

② 股价下降时而OBV线上升，表示买盘旺盛，逢低接手强股，股价可能会止跌回升。

③ OBV线缓慢上升，表示买气逐渐加强，为买进信号。

④ OBV线急速上升，表示力量将用尽为卖出信号。

⑤ OBV线从正的累积数转为负数时，为下跌趋势，应该卖出持有股票。反之，OBV线从负的累积数转为正数时，应该买进股票。

⑥ OBV线最大的用处，在于观察股市盘局整理后，何时会脱离盘局以及突破后的未来走势，OBV线变动方向是重要参考指数，其具体的数值并无实际意义。

⑦ OBV线对双重顶第二个高峰的确定有较为标准的显示，当股价自双重顶第一个高峰下跌又再次回升时，如果OBV线能够随股价趋势同步上升且价量配合，则可持续多头市场并出现更高峰。相反，当股价再次回升时OBV线未能同步配合，却见下降，则可能形成第二个顶峰，完成双重顶的形态，导致股价反转下跌。



### *4.45 PLRC（包含PLRC6、PLRC12）*

#### 4.45.1 指标含义

PLRC，收盘价格线性回归系数（Price Linear Regression Coefficient）。属于趋势型因子。

#### 4.45.2 指标线

PLRC有两条指标线：6日收盘价格线性回归系数，即PLRC6；12日收盘价格线性回归系数，即PLRC12。



### 4.46 PVI

#### 4.46.1 指标含义

PVI，正成交量指标（Positive Volume Index），该指标主要用于辨别目前市场行情是处于多头行情还是空头行情，并追踪市场资金流向。该指标可用于识别资金是否在不动声色地购进股票或抛出，从而得出市场操作策略。该指标属于能量型因子。

#### 4.43.2 计算公式

PVI = PV + [CLS - CLS(n)] + CLS(n) * PV

注：第一次计算时，前一日的NVI一律以100代替，并计算NVI的N天移动平均线。其中，参数N设定为72。

#### 4.43.3 应用法则

① PVI指标位于其N天移动平均线之上时，表示目前处于多头市场；

② PVI指标由下往上穿越其N天移动平均线，代表中期买进讯号。

③ PVI指标位于其N天移动平均线之下时，表示目前处于空头市场。

④ PVI指标由上往下穿越其N天移动平均线时，代表中期卖出讯号。



### 4.44 PVT（包含PTV6、PTV12）

#### 4.44.1 指标含义

PVT，价量趋势指标（Price and Volume Trend），把能量变化与价格趋势有机地联系到了一起，从而构成了量价趋势指标，属于趋势型因子。

#### 4.44.2 指标线

PTV有两条指标线：PTV的6日均值，即PTV6；PTV的12日均值，即PTV12。

#### 4.44.3 计算公式

① 设x = (今日收盘价 - 昨日收盘价) / 昨日收盘价 × 当日成交量；

② PVT指标值为选定计算周期内每日的X值的累加。

#### 4.44.4 应用法则

① 价格上升，PVT指标线下降为卖出信号。

② 价格下跌，PVT指标线上升为买进信号。

③ PVT的用法基本同OBV，但PVT比OBV能更快地反映趋势。



### 4.45 RC（包含RC12、RC24）

#### 4.45.1 指标含义

RC，变化率指数（Rate of Change），类似于动力指数，该指标属于能量型因子。

#### 4.45.2 指标线

RC有两条指标线：12日变化率指数，即RC12；24日变化率指数，即RC24。

#### 4.45.3 计算公式

RT =[CP(t) / CP(t - T)] × 100%

#### 4.45.4 应用法则

① 如果价格始终是上升的，则变化率指数始终在100%线以上，且如果变化速度指数在向上发展时，说明价格上升的速度在加快。

② 如果价格始终是下降的，则变化速度指数始终在100线以下。且如果动力指数向下发展时，说明价格下降的速度在加快。③ 变化率指数也可由其移动平均线来配合研判，两条线的关系与价格线和其平均线的关系相似，买卖信号的取得是与葛兰碧八法则相一致的。

④ 若此比值不乘100，则中位线是1线。但是因为中位线上下区域的标度不对称、图形走样，会给分析者带来不小的麻烦。

⑤ 使用动力指数、变化速度指数进行研判时，无非设定上下警戒区域。当指数顺应价格趋势向上或向下穿过中位线时，视为买进或卖出信号。当这些指数进入上方或下方的警戒区域时，视为超卖或超买信号。当然再一次强调的是，这些指数的研判应顺应大趋势的分析。



### 4.46 ROC（包含ROC6、ROC20）

#### 4.46.1 指标含义

ROC，变动速率（Price Rate of Change），以当日的收盘价和n天前的收盘价比较，通过计算股价某一段时间内收盘价变动的比例，应用价格的移动比较来测量价位动量，达到事先探测股价买卖供需力量的强弱，进而分析股价的趋势及其是否有转势的意愿，（*属于反趋向指标*）属于超买超卖型因子。

#### 4.46.2 指标线

ROC有两条指标线：6日指标线，即ROC6；20日指标线，即ROC20。

#### 4.46.3 计算公式

① ROC = 100 * （收盘价 - n日前的收盘价）/ n日前的收盘价

② MAROC = ROC的m日移动均价

#### 4.46.4 应用法则

① 在趋势明显的涨势或跌势行情中，当ROC由上往下跌破0时，为卖出的时机；当ROC由下往上穿破0时，为买进讯号。

② 在趋势不明显的平衡震荡行情中，当ROC由上往下跌破MAROC时，为卖出时机；当ROC由下往上穿破MAROC时，为买进讯号。

③ 当股价创新低时，而ROC未配合下降，意味着下跌动力减弱，此背离现象应逢低承接；当股价创新高点时，而ROC未配合上升，意味着上涨动力减弱，此背离现象应慎防股价反转而下。

④ 若股价与ROC在低水平同步上升，显示短期趋向正常或短期会有股价反弹现象。

⑤ 若股价与ROC在高水平同步下降，显示短期趋向正常或短期会有股价回落现象。

⑥ ROC波动于“常态范围”内，而上升至第一条超买线时，应卖出股票。

⑦ ROC波动于“常态范围”内，而下降至第一条超卖线时，应买进股票。

⑧ ROC向上突破第一条超买线后，指标继续朝第二条超买线涨升的可能性很大，指标线触碰第二条超买线时，涨势多半将结束。

⑨ ROC向下突破第一条超卖线后，指标继续朝第二条超卖线下跌的可能性很大，指标碰触第二条超卖线时，跌势多半将停止。

⑩ ROC向上穿越第三条超买线时，属于疯狂性多头行情，应尽量不轻易卖出持股。

⑪ ROC向下穿越第三条超卖线时，属于崩溃性空头行情，应克制不轻易买进股票。

⑫ ROC指标穿越第三条超买超卖线时，将股票交给SAR管理，成果相当令人满意。



### 4.47 RVI

#### 4.47.1 指标含义

RVI，相对离散指数（Relative Volatility Index）*（相对活力指数 Relative Vigor Index）*，又称“相对波动性指标”，用于测量价格的发散趋势，用作辅助的确认指标，以配合均线系统、动量指标或其它趋势指标的使用。RVI与RSI类似，但不同于后者之处在于其以价格的方差而不是简单的升跌来测量价格变化的强度，该指标属于超买超卖型因子。

#### 4.47.2 计算公式

① Co = close - open

​     Hl = high - low

② V1 = [ Co + 2 * ref(Co , 1) + 2 * ref(Co , 2) + ref(Co , 3) ] / 6

​     V2 = [ Hl + 2 * ref(Hl , 1) + 2 * ref(Hl , 2) + ref(Hl , 3)] / 6

③ S1 = sum(V1 , n/2)

　 S2 = sum(V2 , n/2)

④ RVI = S1 / S2

​    RVIS = [RVI + 2 * ref(RVI , 1) + 2 * ref(RVI , 2) + ref(RVI , 3)] / 6

注: 

① O——开盘价格；H — 最高价格；L — 最低价格 ；C —收盘价格。

② ref表示引用以前的数据，sum表示累计和，n表示周期（基本设置n/2为10），RVIS是RVI的信号线。

#### 4.47.3 应用法则

RVI是一个以0位中心的摆荡类技术指标，所以其使用方法与其它同类技术指标相似。应用原理：股价上升趋势中，收盘价高于开盘价是大概率事件；在下跌趋势中，收盘价多小于开盘价。

① 判断方式一：RVI与其信号线交叉产生交易信号，下穿信号线时，卖出；上穿信号线时，买入。

② 判断方式二：RVI穿越一定阈值（超买超卖）产生交易信号，以此来观察股价的趋势强度，如：有背离时，趋势弱。



### 4.48 SBM

#### 4.48.1 指标含义

SBM，计算ADTM因子的中间变量，属于超买超卖型因子。（详见ADTM）



### *4.49 SRMI*

#### 4.49.1 指标含义

修正动量指标。属于超买超卖型因子。



### 4.50 STM

STM，计算ADTM因子的中间变量，属于超买超卖型因子。（详见ADTM）



### 4.51 SwingIndex

#### 4.51.1 指标含义

SwingIndex，振动升降指标，计算ASI因子的中间变量，属于趋势型因子。SwingIndex旨在设计出一条感应线，用于代表真实的市场，以对压力线及支撑线的突破及新高、低点的确认、背离等现象作出解释。一方面SwingIndex可以将震荡高点数值化，并界定短期的震荡点，另一方面又可以对市场的内涵作出强力指示。

#### 4.51.2 计算公式

① 先计算出当天最高价与前一天收盘价的绝对值A、当天最低价与前一天收盘价的绝对差B、当天最高价与前一天最低价的绝对值C、前一天收盘价与前一天开盘价的绝对差D，比较A、B、C三者之间的最大值，若A最大，则R = A+1 / 2 * B+ 1 / 4 * D；若B最大，则R = B + 1 / 2 * A + 1 / 4 * D；若C最大，则R = C + 1 / 4 * D。

② X = E + 1 / 2 * F + G

注： E = 当天收盘价 - 前一天收盘价

​        F = 当天收盘价 - 当天开盘价

​       G = 前一天收盘价 - 前一天开盘价

 ③ SI = 50 * X / R * K / L

​       K = A、B两者之间的最大者

​       L = 3

#### 4.51.3 应用法则

① 股价创新高、低，而SI未创新高、低，代表此高低点不确认。

② 股价已突破压力或支撑线，SI却未伴随发生，为假突破。

③ SI前一次形成的显著高、低点，视为SI停损点；多头时，SI跌破前一次低点，停损卖出；空头时，SI向上突破前一次高点，停损回补。



### *4.52 TEMA（包含TEMA5、TEMA10）*

#### 4.52.1 指标含义

TEMA，三重指数移动平均线（Triple Exponential Moving Average），对选定周期内的收盘价分别计算其一至三重指数加权平均，属于均线型因子。TEMA结合了单一EMA、双重EMA和三重EMA，可以提供比这三者更低的滞后。

#### 4.52.2 指标线

TEMA有两条指标线：5日三重指数移动平均线，即TEMA5；10日三重指数移动平均线，即TEMA10。

#### 4.52.3 计算公式



### 4.53 TRIX

#### 4.53.1 指标含义

TRIX，收盘价三重指数平滑移动平均指标（Triple Exponentially Smoothed Average），基于移动平均线理论，对一条平均线进行三次平滑处理，再根据这条移动平均线的变动情况来预测股价的长期走势，属于趋势型因子。

与TRMA等趋向类指标一样，TRIX指标一方面可以忽略价格短期波动的干扰，减少了主力“骗线行为”的干扰，可以避免由于交易行为过于频繁而造成较大交易成本的浪费；另一方面保留了移动平均线的效果，凸现股价未来长期运动趋势，使投资者对于未来较长时间内的股价运动趋势有直观、准确的了解，从而可以降低投资者深度套牢和跑丢“黑马”的风险。

#### 4.53.2 指标线

TRIX有两条指标线：5日收盘价三重指数平滑移动平均指标，即TRIX5；10日收盘价三重指数平滑移动平均指标，即TRIX10。

#### 4.53.3 计算公式

① TR = 收盘价的n日指数移动平均；

② TRIX = (TR - 昨日TR) / 昨日TR * 100；

③ MATRIX = TRIX的m日简单移动平均；

#### 4.53.4 应用法则

打算进行长期控盘或投资时，趋向类指标中以TRIX最适合。

① TRIX 由下向上交叉TMA时，短线买进；

② TRIX由上向下交叉TMA时，短线卖出；

③ TRIX与股价产生背离时，应注意随时反转；

④ 中长线的操作中，以TRIX上穿0轴线为买进信号，以TRIX跌穿0轴线为卖出信号。

注：盘整行情时，此指标不适用。



### *4.54 TVMA*

#### 4.54.1 指标含义

TVMA，成交金额的移动平均值（Turnover Value Moving Average），属于成交量型因子。

#### 4.54.2 指标线

TVMA有两条指标线：6日成交金额的移动平均值，即TVMA6；20日成交金额的移动平均值，即TVMA20。



### *4.55 TVSTD*

#### 4.55.1 指标含义

TVSTD，成交金额的标准差（Turnover Value Standard Deviation），属于成交量型因子。

#### 4.55.2 指标线

TVSTD有两条指标线：20日成交金额的标准差，即TVSTD6；20日成交金额的标准差，即TVSTD20。



### *4.56 Ulcer*

#### 4.56.1 指标含义

Ulcer，由Peter Martin于1987年提出，1989年发表于Peter Martin和Byron McCann的著作The Investors Guide to Fidelity Funds，用于考察向下的波动性。该指标属于趋势型因子。

#### 4.56.2 指标线

Ulcer包含两条指标线：Ulcer5、Ulcer10。



### 4.57 UOS

#### 4.57.1 指标含义

UOS，终极指标（Ultimate Oscillator），一种多方位功能的指标，除了确认趋势与超买超卖方面的作用之外，它的“突破”讯号不仅可以提供适当的交易时机，还能进一步加强指标的可靠度。现行使用的各种振荡指标，对于周期参数的选择相当敏感，不同市况、不同参数设定的振荡指标，产生的结果截然不同，因此，选择最佳的参数组合，成为使用振荡指标之前最重要的一道手续。该指标属于趋势型因子。

#### 3.57.2 计算公式

① TH = 今日最高价和昨日收盘价的较大值

② TL = 今日最低价和昨日收盘价的较小值

③ ACC1 =（收盘价 - TL）与（TH - TL）两者N1日累和之比

④ ACC2 =（收盘价 - TL）与（TH - TL）两者N2日累和之比

⑤ ACC3 =（收盘价 - TL）与（TH - TL）两者N3日累和之比

④ UOS =（ACC1 * N2 * N3 + ACC2 * N1 * N3 + ACC3 * N1 * N2) * 100 / (N1 * N2 + N1 * N3 + N2 * N3)

⑤ MAUOS = UOS的m日指数平滑移动平均

#### 3.57.3 应用法则

① UOS指标上升至50～70之间，随后向下跌破50时，是短线卖出讯号；当UOS向上突破65时，可视为短线的投机性买进讯号。

② UOS指标上升至70以上，随后又向下跌破70时，是中线卖出讯号；UOS指标下跌至35以下，随后向上回升突破35时，视为中线买进讯号。这一点在股价走上升形态时，效果更加明显。

③ 股价创新高点，UOS指标并未伴随创新高，两者产生“背离”时，是多头趋势即将结束的警告讯号。注意必须位于50之上，其多头背离讯号才可信任。

④ 股价创新低点，UOS指标并未伴随创新低，两者产生“背离”时，是空头趋势即将结束的警告讯号。注意必须最低下跌至35以下，其空头“背离”讯号才可信任。

⑤ 多头背离现象发生后，UOS指标向下跌破其背离区的N字波低点时，是中线卖出的确认讯号。；空头“背离”现象发生后，UOS指标向上突破其“背离”区的N字形高点时，是中线买进的确认讯号。

⑥ uos短线抄底：uos上穿50。

⑦ uos短线卖顶：uos下穿65。

⑧ uos中长期抄底：uos上穿35。

⑨ uos中长期卖顶：uos下穿70。

注：

① 市场上的的买卖循环主要有长期、中期和短期三种，价格在波动过程中的山长的额力量都是要依靠这些循环时间周期来进行的，所以在运用UOS指标的时候，必须要注意分别计算长期、中期和短期的不同的影响力。

② 市场上，不同时期的循环影响力都是不一样的。所以，在计算市场上的购买力量的时候，一定要依照其不同的影响加以区分。

③ 要计算当个交易日内于真实低位TL的差距和举例TR真实波幅指标所占的比重。



### *4.58 UpRVI*

#### 4.58.1 指标含义

UpRVI，计算RVI因子的中间变量，属于超买超卖型因子。



### 4.59 VDEA 

#### 4.59.1 指标含义

VDEA，计算VMACD因子的中间变量，属于成交量型因子。（详见VMACD）



### 4.60 VDIFF

#### 4.60.1 指标含义

VDIFF，计算VMACD因子的中间变量，属于成交量型因子。（详见VDIFF）



### *4.61 VEMA*

#### 4.61.1 指标含义

VEMA，成交量的指数移动平均值，属于成交量型因子。

#### 4.61.2 指标线

VEMA包含三条指标线：成交量的5日指数移动平均，即VEMA5；成交量的10日指数移动平均，即VEMA10；成交量的12日指数移动平均，即VEMA12；成交量的26日指数移动平均，即VEMA26。

#### 4.61.3 计算公式



### 4.62 VMACD（包含VDEA、VDIFF）

#### 4.62.1 指标含义

VMACD，成交量指数平滑异同移动平均线（Volume Moving Average Convergence and Divergence），VMACD的意义和MACD基本相同， 但VMACD取用的数据源是成交量，MACD取用的数据源是成交价格。该指标属于成交量型因子。

#### 4.62.2 计算公式

先计算成交量的短期(SHORT)和长期(LONG)指数平滑移动平均线，再推算VDIFF和VDEA及两者之差，最后得出VMACD。具体计算公式：

① SHORT = [2 * 成交量 ＋（N－1）× 上一周期成交量]

② LONG = [2 * 成交量＋（N1－1）× 上一周期成交量]

③ VDIFF= SHORT － LONG

④ VDEA = [2 * VDIFF ＋（M－1）* 上一周期VDIFF]

⑤ VMACD = VDIFF － VDEA

注：在参数设置中，N = 12；N1 = 26；M = 9。

#### 4.62.3 应用法则

① VDIFF与VDEA均为正值，两者均在零轴线之上时，VDIFF向上突破VDEA为买入信号。

② VDIFF与VDEA均为负值，两者均在零轴线之下时，VDIFF向下跌破VDEA为卖出信号。

③ VDEA线与K线趋势发生背离时为行情反转信号。

④ 分析VMACD柱状线，由红变绿（正变负）为卖出信号；由绿变红为买入信号。

⑤ VDIFF与VDEA均为负值时，常常会两线长期粘合，当两线有效分离且VDIFF在上时为中线买入信号。



### 4.63 VOSC

#### 4.63.1 指标含义

VOSC，成交量震荡（Volume Oscillator），又称移动平均成交量指标，但它并非仅仅计算成交量的移动平均线，而是通过对成交量的长期移动平均线和短期移动平均线之间的比较，分析成交量的运行趋势和及时研判趋势转变方向。该指标属于成交量型因子。

#### 4.63.2 计算公式

① SHORT = N周期中成交量的总和 / n；

② LONG = M周期中成交量的总和 / m；

③ VOSC =（SHORT － LONG）/ SHORT * 100。

注：

① SHORT计算短期移动平均成交量的天数，N一般取12天；

② LONG计算长期移动平均成交量的天数，M一般取26天。

#### 4.63.3 应用法则

① 若VOSC指标为正数，表示成交量趋升，交投活跃。当VOSC指标为负数，则成交量趋降，交投趋弱。

② 在短期的股价波动中，VOSC指标的顶底往往会与股价的短期顶底同时出现。但在股价长期趋势中，VOSC指标的重要顶部或底部却往往会比股价的重要顶部或底部提前一段时间出现，这种情况产生的根源是：在实际走势中，量能的变化往往先于股价的变化。

③ 当VOSC下降到极低的位置，至少是小于-100，最适合的是小于-200时，如果VOSC指标能以极快的速率上升并上穿0轴线时，是短线最佳买入机会。



### 4.64 VR

#### 4.64.1 指标含义

VR，成交量比率（Volume Ratio），基于“反市场操作”的原理，通过分析股价上升日成交额（或成交量）与股价下降日成交额（或成交量）的比值，从而掌握市场买卖气势。该指标属于成交量型因子。

#### 4.64.2 计算公式

① T日内，股价上涨日的成交量定义为AV，所有AV加总后定义为AVS；

② T日内，股价下跌日的成交量定义为BV，所有BV加总后定义为BVS；

③ T日内，若交易日的股价没有涨跌变化，则将该日的成交量定义为CV，所有的CV加总后称为CVS；

④ 计算周期为T的VR：

VR =（AVS + 1 / 2CVS）/（BVS + 1 / 2 CVS）

注：周期T的参数可以自定义设定，但是T值不宜小于12，否则，采样天数不足容易造成偏差。

#### 4.64.3 应用法则

一般而言，VR的理论取值在**0**至**正无穷大**之间，可将其分为四个区间：低价区域（40 ~ 70）、安全区域（80 ~ 150）、获利区域（160 ~ 350）与警戒区域（350以上）。

① 当VR ＞ 350时，为警戒区域。此时应有高档危机意识，随时注意控制风险。当VR ＞ 450时，市场成交过热，应反向卖出；

② 当VR ＜ 40时，市场成交低迷，市场极易形成底部，部分资金会进入市场而股价反弹，应积极买进。当VR位于40 ~ 70时，可以考虑选股跟进。当VR位于80 ~ 150时，股价波动较小，可以持有。当VR位于160 ~ 350时，由于大部分资金已经进入市场，后续资金乏力，如果股价不断上涨，VR值增加，可以把握高位出货。

③ VR值一般分布在150左右最多。若VR长期在150附近盘整，一旦越过250时，市场极易产生一段多头行情；若VR指标由抵挡直接上升至250，股价仍未遭受阻力，投资者要积极选股买进。

注：

① 使用这个指标时，很多人关注的是基本用法中所提到的40以下与400以上两个区域，往往通过这种方法去判断个股在行情中高点与低点。其实，投资者应特别注意另一个比较关键的数值——250，这个数值对于观察股价上涨有着非常重要的作用。

② 虽然我们不能忽视40、400这两个数值在VR指标中判断底部与头部的辅助作用，但是股价脱离底部区域是否进入拉升阶段不是以VR突破40为标准的，而应该以VR突破250为标准；有个别股票在它启动阶段会有比较大的涨幅，但VR没有突破250，或刚突破250就回落下来，这说明该股还没有进入其拉升阶段。



### 4.65 VROC

#### 4.65.1指标含义

VROC，量变动速率指标（Volume Rate of Change），以当日的成交量和n天前的成交量比较，通过计算某一段时间内成交量变动的幅度，应用成交量的移动比较来测量成交量运动趋向，达到事先探测成交量供需的强弱，进而分析成交量的发展趋势及其将来是否有转势的意愿，*属于成交量的反趋向指标。该指标属于成交量型因子。*

#### 4.65.2 指标线

VROC有两条指标线：6日量变动速率指标，即VROC6；12日量变动速率指标，即VROC12。

#### 4.65.3 计算公式

VROC ＝（成交量 － n日前的成交量）/ n日前的成交量 * 100

注：n值表示间隔天数，一般取12。

#### 4.65.4 应用法则

① VROC向下跌破零，预示有主流资金撤退迹象；

②  VROC向上突破零，预示有主流资金介入迹象；

③ 股价创新高，VROC未配合上升，显示上涨动力减弱；

④ 股价创新低，VROC未配合下降，显示下跌动力减弱；

⑤ 股价与VROC从低位同时上升，表示趋势仍有上升动能；

⑥ 股价与VROC从高位同时下降，表示趋势仍有下跌动能。



### *4.66 VSTD*

#### 4.66.1 指标含义

VSTD，成交量标准差（Volume Standard Deviation），考察成交量的波动程度，属于成交量型因子。

#### 4.66.2 指标线

VSTD包含两条指标线：10日成交量标准差，即VSTD10；20日成交量标准差，即VSTD20。

#### 4.66.2 计算法则

① 当股价已经创出新高而VSTD指标未能创出新高时，需保持谨慎，股价随时有下跌的可能。

② VSTD指标最显著的作用是在于对股价顶部的研判，具有非常明确及时的效果。当VSTD指标值快速上升到极高的位置时，一旦出现滞涨或回落迹象，就是短线卖出信号。



### 4.67 AccountsPayablesTDays

#### 4.67.1 指标含义

AccountsPayablesTDays，应付账款周转天数（Accounts payable turnover days），属于营运能力类因子。

#### 4.67.2 计算公式

应付账款周转天数 = 360 / 应付账款周转率



### 4.68 AccountsPayablesTRate

#### 4.68.1 指标含义

AccountsPayablesTRate，应付账款周转率，属于营运能力类因子。

#### 4.68.2 计算公式

应付账款周转率 = 营业成本 /（应付账款 + 应付票据 + 预付款项）



### 4.69 AdminiExpenseRate

#### 4.69.1 指标含义

AdminiExpenseRate，管理费用与营业总收入之比，属于盈利能力和收益质量类因子。

#### 4.69.2 计算公式

管理费用与营业总收入之比 = 管理费用 / 营业总收入



### 4.70 ARTDays 

#### 4.70.1 指标含义

ARTDays，应收账款周转天数（Accounts receivable turnover days），属于营运能力类因子。

#### 4.70.2 计算公式

应收账款周转天数 = 360 / 应收账款周转率



### 4.71 ARTRate

#### 4.71.1 指标含义

ARTRate，应收账款周转率（Accounts receivable turnover rate），属于营运能力类因子。

#### 4.71.2 计算公式

应收账款周转率 = 营业收入 /（应收账款+应收票据+预收账款）



### 4.72 ASSI

#### 4.72.1 指标含义

ASSI，对数总资产（Natural logarithm of total assets），属于估值与市值类因子。

#### 4.72.2 计算公式

对数总资产 = 总资产的对数



### 4.73 BLEV

#### 4.73.1 指标含义

BLEV，账面杠杆（Book leverage），属于偿债能力和资本结构类因子。

#### 4.73.2 计算公式

账面杠杆 = 非流动负债合计 / 股东权益



### 4.74 BondsPayableToAsset

#### 4.74.1 指标含义

BondsPayableToAsset，应付债券与总资产之比（Bonds payable to total assets），属于偿债能力和资本结构类因子。

#### 4.74.2 计算公式

应付债券与总资产之比 = 应付债券 / 总资产



### 4.75 CashRateOfSales

#### 4.75.1 指标含义

CashRateOfSales，经营活动产生的现金流量净额与营业收入之比（Cash rate of sales），属于现金流指标因子。

#### 4.75.2 计算公式

经营活动产生的现金流量净额与营业收入之比 = 经营活动产生的现金流量净额 / 营业收入



### 4.76 CashToCurrentLiability

#### 4.76.1 指标含义

CashToCurrentLiability，现金比率（Cash to current liability），属于现金流指标因子。

#### 4.76.2 计算公式

现金比率 = 期末现金及现金等价物余额 / 流动负债合计



### 4.77 CMRA

#### 4.77.1 指标含义

24 月累计收益（Monthly cumulative return range over the past 24 months），属于超买超卖型因子。



### 4.78 CTOP

#### 4.78.1 指标含义

现金流市值比（Cash flow to price），属于现金流指标因子。

#### 4.78.2 计算公式

现金流市值比 = 每股派现（税前）* 分红前总股本 / 总市值



### 4.79 CTP5

#### 4.79.1 指标含义

CTP5，5年平均现金流市值比（Five-year average cash flow to price），属于现金流指标因子。

#### 4.79.2 计算公式

5年平均现金流市值比 = 近五年每股派现（税前）* 分红前总股本 / 近五年总市值



### 4.80 CurrentAssetsRatio

#### 4.80.1 指标含义

CurrentAssetsRatio，流动资产比率（Current assets ratio），属于偿债能力和资本结构类因子。

#### 4.80.2 计算公式

流动资产比率 = 流动资产合计 / 总资产



### 4.81 CurrentAssetsTRate

#### 4.81.1 指标含义

CurrentAssetsTRate，流动资产周转率（Current assets turnover rate），属于营运能力类因子。

#### 4.81.2 计算公式

流动资产周转率 = 营业收入 / 流动资产合计



### 4.82 CurrentRatio

#### 4.82.1 指标含义

CurrentRatio，流动比率（Current ratio），属于偿债能力和资本结构类因子。

#### 4.82.2 计算公式

流动比率 = 流动资产合计 / 流动负债合计



### *4.83 DAVOL*

#### 4.83.1 指标含义

DAVOL，属于成交量型因子。

#### 4.83.2 计算公式

① DAVOL5 = 5日平均换手率 / 120日平均换手率

② DAVOL10 = 10日平均换手率 / 120日平均换手率

③  DAVOL20 = 20日平均换手率 / 120日平均换手率



### 4.84 β

#### 4.84.1 指标含义

Beta coefficient，β系数，是一种风险指数，用于衡量个股或股票基金相对于股市的价格波动情况，属于评估证券系统性风险的工具。Beta系数起源于资本资产定价模型，它的真实含义就是特定资产（或资产组合）的系统风险度量。

#### 4.84.2 相关因子

DDNBT，即下跌贝塔（Downside beta）；HBETA，历史贝塔（Historical daily beta）。

#### 4.84.3 计算公式

①  ![4.48 β系数计算公式](C:\Users\Administrator\Desktop\API 说明文档 图片\4.48 β系数计算公式.png)

其中Cov(ra , rm)是证券 *a* 的收益与市场收益的协方差；![{\sigma_m^2}](http://wiki.mbalib.com/w/images/math/3/1/7/3175f3b02ddfe7521e3f57bad08f8957.png)是市场收益的方差。

② 由于Cov(ra,rm) = ρam * σa * σm，

所以， ![4.48 贝塔的计算公式2 ](C:\Users\Administrator\Desktop\API 说明文档 图片\4.48 贝塔的计算公式2 .png)

注：

① 其中ρam为证券 a 与市场的相关系数；σa为证券 a 的标准差；σm为市场的标准差。

② 据此公式，贝塔系数并不代表证券价格波动与总体市场波动的直接联系。不能绝对地认为：β越大，σa相对于σm越大；β越小，σa相对于σm越小。甚至，即使β = 0也不能代表证券无风险，而是有可能是证券价格波动与市场价格波动无关（ρam = 0）；但是可以确定，如果证券无风险（σa），β一定为零。

#### 4.84.4 应用原理

可以根据市场走势预测选择不同贝塔系数的证券从而获得额外收益，特别适用于作为波段操作使用。在股价处于上涨趋势时，应选择贝塔系数高的证券，以放大市场收益率；在股价处于下跌趋势时，应选择贝塔系数较低的证券。

① 若β为正值，则表示该单项资产的风险收益率与市场组合平均风险收益率的涨跌同向变动；若为负值，则两者反向变动。

② β = 1，表示该单项资产的风险收益率变动幅度与市场组合的平均水平同比例变化，其风险情况与市场平均水平的风险情况一致； 

​    若 |β| ＞ 1，说明该单项资产的风险收益率变动幅度大于市场组合的平均水平，则该单项资产的风险程度大于整个市场投资组合的风险； 
​    若 |β| ＜ 1，说明该单项资产的风险收益率变动幅度小于市场组合的平均水平，则该单项资产的风险程度小于整个市场投资组合的风险。



### *4.89 HSIGMA* 

#### 4.89.1 指标含义

HSIGMA，历史波动（Historical daily sigma），过往12个月中，个股日收益关于市场组合日收益的三阶自回归，市场组合日收益的残差标准差，属于超买超卖型因子。



### 4.90 IntangibleAssetRatio

#### 4.90.1 指标含义

IntangibleAssetRatio，无形资产比率（Intangible assets ratio），属于偿债能力和资本结构类因子。

#### 4.90.2 计算公式

无形资产比率 = (无形资产 + 研发支出 + 商誉) / 总资产



### 4.91 InventoryTDays

#### 4.91.1 指标含义

InventoryTDays，存货周转天数（Inventory turnover days），属于营运能力类因子。

#### 4.91.2 计算公式

存货周转天数 = 360 / 存货周转率



### 4.92 InventoryTRate

#### 4.92.1 指标含义

InventoryTRate，存货周转率（Inventory turnover rate），属于营运能力类因子。

#### 4.92.2 计算公式

存货周转率 = 营业成本 / 存货



### 4.93 InvestCashGrowRate

#### 4.93.1 指标含义

InvestCashGrowRate，投资活动产生的现金流量净额增长率（Growth rate of cash flows from investments），属于现金流指标因子。

#### 4.93.2 计算公式

投资活动产生的现金流量净额增长率 = 当年投资活动产生的现金流量净额 / 前一年投资活动产生的现金流量净额 - 1



### 4.94 LCAP

#### 4.94.1 指标含义

LCAP，对数市值（Natural logarithm of total market values），属于估值与市值类因子。

#### 4.94.2 计算公式

对数市值 = 市值的对数



### 4.95 LFLO

#### 4.95.1 指标含义

LFLO，对数流通市值（Natural logarithm of float market values），属于估值与市值类因子。

#### 4.95.2 计算公式

对数流通市值 = 流通市值的对数



### 4.96 LongDebtToAsset

#### 4.96.1 指标含义

LongDebtToAsset，长期借款与资产总计之比（Long term loan to total assets），属于偿债能力和资本结构类因子。

#### 4.96.2 计算公式

长期借款与资产总计之比 = 长期借款 / 总资产



### 4.97 LongDebtToWorkingCapital

#### 4.97.1 指标含义

LongDebtToWorkingCapital，长期负债与营运资金比率（Long term debt to working capital），属于偿债能力和资本结构类因子。

#### 4.97.2 计算公式

长期负债与营运资金比率 = 非流动负债合计 / (流动资产合计 - 流动负债合计)



### 4.98 LongTermDebtToAsset

#### 4.98.1 指标含义

LongTermDebtToAsset，长期负债与资产总计之比（Long term debt to total assets），属于偿债能力和资本结构类因子。

#### 4.98.2 计算公式

长期负债与资产总计之比 = 非流动负债合计 / 总资产



### 4.99 MA

#### 4.99.1 指标含义

MA，移动均线（Moving average），具有趋势的特性，比较平稳，不同于K线的起起落落震荡。该指标用于趋势追踪，具有识别已经终结或反转趋势的功能，但是具有一定的滞后性，属于均线型因子。

#### 4.99.2 指标线

MA有5条指标线：5日移动均线，即MA5；10日移动均线，即MA10；20日移动均线，即MA20；60日移动均线，即MA60；120日移动均线，即MA120。

#### 4.99.3 计算公式

n日移动平均线 = n日收市价之和 / n

#### 4.99.4 应用法则

① 移动平均线从下降逐渐走平且略向上方抬头，而股价从移动平均线下方向上方突破，为买进信号。

② 股价位于移动平均线之上运行，回档时未跌破移动平均线后又再度上升时为买进时机。

③ 股价位于移动平均线之上运行，回档时跌破移动平均线，但短期移动平均线继续呈上升趋势，此时为买进时机。

④ 股价位于移动平均线以下运行，突然暴跌，距离移动平均线太远，极有可能向移动平均线靠近(物极必反，下跌反弹)，此时为买进时机。

⑤ 股价位于移动平均线之上运行，连续数日大涨，离移动平均线愈来愈远，说明近期内购买股票者获利丰厚，随时都会产生获利回吐的卖压，应暂时卖出持股。

⑥ 移动平均线从上升逐渐走平，而股价从移动平均线上方向下跌破移动平均线时说明卖压渐重，应卖出所持股票。

⑦ 股价位于移动平均线下方运行，反弹时未突破移动平均线，且移动平均线跌势减缓，趋于水平后又出现下跌趋势，此时为卖出时机。

⑧ 股价反弹后在移动平均线上方徘徊，而移动平均线却继续下跌，宜卖出所持股票。



### *4.100 MAWVAD*

MAWVAD，因子WVAD的6日均值，属于超买超卖型因子。



### 4.101 MLEV

#### 4.101.1 指标含义

MLEV，市场杠杆（Market leverage），属于偿债能力和资本结构类因子。

#### 4.101.2 计算公式

市场杠杆 = 非流动负债合计 /（非流动负债合计 + 总市值） 



### 4.102 NetAssetGrowRate 

#### 4.102.1 指标含义

NetAssetGrowRate，净资产增长率（Net assets growth rate），属于成长能力类因子。

#### 4.102.2 计算公式

净资产增长率 = 今年股东权益 / 去年股东权益 - 1



### 4.103 NetProfitGrowRate

#### 4.103.1 指标含义

NetProfitGrowRate，净利润增长率（Net profit growth rate），属于成长能力类因子。

#### 4.103.2 计算公式

净利润增长率 = 今年净利润 / 去年净利润 - 1



### 4.104 NetProfitRatio

#### 4.104.1 指标含义

NetProfitRatio，销售净利率（Net profit ratio），属于盈利能力和收益质量类因子。

#### 4.104.2 计算公式

销售净利率 = 净利润 / 营业收入



### 4.105 NOCFToOperatingNI

#### 4.105.1 指标含义

NOCFToOperatingNI，经营活动产生的现金流量净额与经营活动净收益之比，属于现金流指标因子。

#### 4.105.2 计算公式

NOCFToOperatingNI = 经营活动产生的现金流量净额 /（营业总收入 - 营业总成本）



### 4.106 NonCurrentAssetsRatio

#### 4.106.1 指标含义

NonCurrentAssetsRatio，非流动资产比率（Non-current assets ratio），属于偿债能力和资本结构类因子。

#### 4.106.2 计算公式

非流动资产比率 = 非流动资产合计 / 总资产



### 4.107 NPParentCompanyGrowRate

#### 4.107.1 指标含义

NPParentCompanyGrowRate，归属母公司股东的净利润增长率，属于成长能力类因子。

#### 4.107.2 计算公式

归属母公司股东的净利润增长率 = 当年归属于母公司所有者的净利润 / 前一年归属于母公司所有者的净利润 - 1



### 4.108 NPToTOR

#### 4.108.1 指标含义

NPToTOR，净利润与营业总收入之比（Net profit to total operating revenues），属于盈利能力和收益质量类因子。

#### 4.108.2 计算公式

净利润与营业总收入之比 = 净利润 / 营业总收入



### 4.109 OperatingExpenseRate

#### 4.109.1 指数含义

OperatingExpenseRate，营业费用与营业总收入之比（Operating expense rate），属于盈利能力和收益质量类因子。

#### 4.109.2 计算公式

营业费用与营业总收入之比 = 销售费用 / 营业总收入



### 4.110 OperatingProfitGrowRate

#### 4.110.1 指标含义

OperatingProfitGrowRate，营业利润增长率（Operating profit growth rate），属于成长能力类因子。

#### 4.110.2 计算公式

营业利润增长率 = 今年营业利润 / 去年营业利润 - 1



### 4.111 OperatingProfitRatio 

#### 4.111.1 指标含义

OperatingProfitRatio，营业利润率（Operating profit ratio），属于盈利能力和收益质量类因子。

#### 4.111.2 计算公式

营业利润率 = 营业利润 / 营业收入



### 4.112 OperatingProfitToTOR

#### 4.112.1 指标含义

OperatingProfitToTOR，营业利润与营业总收入之比（Operating profit to total operating revenues），属于盈利能力和收益质量类因子。

#### 4.112.2 计算公式

营业利润与营业总收入之比 = 营业利润 / 营业总收入



### 4.113 OperatingRevenueGrowRate

#### 4.113.1 指标含义

OperatingRevenueGrowRate，营业收入增长率（Operating revenue growth rate），属于成长能力类因子。

#### 4.113.2 计算公式

营业收入增长率 = 今年营业收入 / 去年营业收入 - 1



### 4.114 OperCashGrowRate

#### 4.114.1 指标含义

OperCashGrowRate，经营活动产生的现金流量净额增长率，属于现金流指标因子。

#### 4.114.2 计算公式

OperCashGrowRate = 今年经营活动产生的现金流量净额 / 去年经营活动产生的现金流量净额 - 1



### 4.115 OperCashInToCurrentLiability

#### 4.115.1 指标含义

OperCashInToCurrentLiability，现金流动负债比（Cash provided by operations to current liability），属于现金流指标因子。

#### 4.115.2 计算公式

现金流动负债比 = 经营活动产生的现金流量净额 / 流动负债合计



### 4.116 PB

#### 4.116.1 指标含义

PB，市净率（Price-to-book ratio），属于估值与市值类因子。

#### 4.116.2 计算公式

市净率 = 总市值 / 归属于母公司所有者权益合计



### 4.117 PCF

#### 4.117.1 指标含义

PCF，市现率（Price-to-cash-flow ratio），属于估值与市值类因子。

#### 4.117.2 计算公式

PCF = 总市值 / 经营活动产生的现金流量净额



### 4.118 PE

#### 4.118.1 指标含义

PE，市盈率（Price-earnings ratio），属于估值与市值类因子。

#### 4.118.2 计算公式

市盈率 = 总市值 / 归属于母公司所有者的净利润



### 4.119 PS

#### 4.119.1 指标含义

PS，市销率（Price-to-sales ratio），属于估值与市值类因子。

#### 4.119.2 计算公式

市销率 = 总市值 / 营业总收入



### 4.120 PSY

#### 4.120.1 指标含义

PSY，心理线指标（Psychological line index），将一定时期内投资者趋向买方或卖方的心理事实转化为数值，用于判断股价的未来趋势，属于能量型因子。

#### 4.120.2 计算公式

PSY = n日内上涨的天数 / n * 100

注：n的值一般设为10或者12。

#### 4.120.3 应用法则

① 一段下跌（上升）行情展开前，超买超卖的最高（低）点通常会出现两次。在出现第二次超买（超卖）的最高（低）点时，一般是卖出（买进）时机。由于PSY指标具有这种高点密集出现的特性，可给投资者带来充裕时间进行研判与介入。

② PSY指标在25～75之间为常态分布，在此区间一般应持观望态度。

③ PSY指标超过75或低于25时，表明股价开始步入超买区或超卖区，此时需要留心其动向。当PSY指标百分比值超过83或低于17时，表明市场出现超买区或超卖区，价位回跌或回升的机会增加，投资者应该准备卖出或买进，不必在意是否出现第二次信号。这种情况在个股中比较多见。

④ 当PSY指 标 < 10时，是极度超卖。抢反弹的机会相对提高，此时为短期较佳的买进时机；若PSY指标百分比值 > 90，是极度超买。此时为短期卖出的有利时机。

⑤ 当PSY曲线和PSYMA曲线同时向上运行时，为买入时机；当PSY曲线与PSYMA曲线同时向下运行时，为卖出时机。而当PSY曲线向上突破PSYMA曲线时，为买入时机；相反，当PSY曲线向下跌破PSYMA曲线后，为卖出时机。

⑥ 当PSY曲线向上突破PSYMA曲线后，开始向下回调至PSYMA曲线，只要PSY曲线未能跌破PSYMA曲线，都表明股价属于强势整理。一旦PSY曲线再度返身向上时，为买入时机；当PSY曲线和PSYMA曲线同时向上运行一段时间后，PSY曲线远离PSYMA曲线时，一旦PSY曲线掉头向下，说明股价上涨的动能消耗较大，为卖出时机。

⑦ 当PSY曲线和PSYMA曲线再度同时向上延伸时，投资者应持股待涨；当PSY曲线在PSYMA曲线下方运行时，投资者应持币观望。

⑧ 当PSY曲线和PSYMA曲线始终交织在一起，于一个波动幅度不大的空间内运动时，预示着股价处于盘整的格局中，投资者应以观望为主。



### 4.121 QuickRatio

#### 4.121.1 指标含义

QuickRatio，速动比率（Quick ratio），属于偿债能力和资本结构类因子。

#### 4.121.2 计算公式

速动比率 =（流动资产合计 - 存货）/ 流动负债合计



### *4.122 REVS*

#### 4.122.1 指标含义

REVS，股票收益，属于超买超卖型因子。

#### 4.122.2 指标线

REVS包含三条指标线：股票的5日收益，即REVS5；股票的10日收益，即REVS10；股票的15日收益，即REVS50



### 4.123 ROA

#### 4.123.1 指标定义

ROA，资产回报率（Return on assets），属于盈利能力和收益质量类因子。

#### 4.123.2 计算公式

资产回报率 = 净利润 / 总资产



### 4.124 ROA5

#### 4.124.1 指标含义

ROA5，5年资产回报率（Five-year average return on assets），属于盈利能力和收益质量类因子。

#### 4.124.2 计算公式

5年资产回报率 = 净利润 / 总资产



### 4.125 ROE

#### 4.125.1 指标含义

ROE，权益回报率（Return on equity），属于盈利能力和收益质量类因子。

#### 4.125.2 计算公式

权益回报率 = 净利润 / 股东权益



### 4.126 ROE5

#### 4.126.1 指标含义

ROE5，5 年权益回报率（Five-year average return on equity），股东权益。属于盈利能力和收益质量类因子。

#### 4.126.2 计算公式

5年权益回报率 = 净利润 / 股东权益



### 4.127 RSI

#### 4.17.1 指数含义

RSI，相对强弱指标（Relative Strength Index），通过比较一段时期内的平均收盘涨数和平均收盘跌数来分析市场买沽盘的意向和实力，据此预测趋势的持续或者转向，属于超买超卖型因子。

#### 4.127.2 计算公式

① RS = n日内收市价上涨幅度总和 / n日内收市价下跌幅度总和

② RSI = 100 - 100 /（1 + RS）

#### 4.127.3 指标线

RSI需要设置三条指标线，参数为N1、N2、N3；统计天数，一般设置为6、12、24。N值越大，趋势越强，但是有反应滞后倾向，称为慢速线；N值越小，变化相对越敏感，称为快速线。

#### 4.127.4 应用原理

RSI反应了股价变动的四个因素：上涨天数、下跌天数、上涨幅度以及下跌幅度。根据正态分布理论，随机变数在靠近中心数值附近区域出现的概率最大。在股市的长期发展过程中，绝大多数时间里相对强弱指数的变化范围介于30 ~ 70之间，其中又以40 ~ 60区间内的概率最大。超过80或者低于20的概率较少，高于90或低于10的概率又次之。

① 三条RSI指标线的超买超卖的标准是各不相同的，以6日RSI为例：80以上为超买区，股价容易形成短期回档；20以下为超卖区，股价容易形成短期反弹。在强势涨升时，可在RSI指标附近呈M头时卖出；在急跌下降时，可在RSI指标20附近呈W底时买进。

② 在股价创新高点，同时RSI也创新高点时，表示后市仍强，若RSI未创新高点，则为卖出信号；在股价创新低点，RSI也创新低点，则后市仍弱，若RSI未创新低点，则为买进信号。

③ 盘整期中RSI指标一底比一底高，为多头强势，后势可能再涨一段，是买进时机；反之，RSI指标一底比一底低是卖出时机。

④ 若股价尚在盘整阶段，而RSI已整理完成，则股价随之突破整理区。

⑤ 短期的RSI在20以下的水平，由下往上交叉长期的RSI时，为买进信号；短期的RSI在80以上的水平，由上往下交叉长期的RSI时，为卖出信号。

⑥ RSI指标的背离作用比较明显，一般转势的信号，代表着大势反转。如果股价一波比一波信号低，相反的RSI却一波比一波高，股价很容易反转下跌。

⑦ 当RSI与股价出现背离时，投资者应选择正确的买卖时机。结合快速与慢速两条线来确定买卖时机：把6日线与12日线RSI结合起来使用。当图形上6日RSI线向上突破12日RSI线时，即为买进的信号；当6日RSI线向下跌破12日RSI线时，即为卖出信号。尤其当RSI 处于低位30以下发出的买进信号与高位70以上发出的卖出信号极为可靠。

⑧ RSI在50以下为弱势市场，50以上为强势市场。RSI原本处于50中界限以下的弱势区，然后向上扭转突破50分界，代表股价已经转强；RSI原本处于50中界线以上的强势区，然后向下扭转跌破50分线界，代表股价已转弱。RSI在50以下的准确性较高。

⑨ 连接RSI连续的两个底部，画出一条由左向右上方倾斜的切线，这时RSI指标会构成上升支持线，如果RSI指标跌破该支持线，投资者需要果断卖出。上升支持线呈现15度至30度时，最具支撑意义，如果支撑线的角度太陡，将会很容易被突破，失去支撑意义。

⑩ 连接RSI连续的两个峰顶，画出一条由左向右下方倾斜的切线，这时会出现形成下降压力线，如果RSI指标能够穿越该压力线时，投资者可以选择买进。下降压力线呈负30至负15度时，最具反压意义。如果反压线的角度太陡，很快会被突破，失去反压意义。

⑪ RSI可依头肩顶、头肩底、三角行等形态作买卖点的讯号。RSI的M形走向是超买区常见的见顶形态；W形走向是超卖区常见的见底形态。这时，往往可见RSI走向与价格走向发生背离。



### 4.128 RSTR12

#### 4.128.1 指标含义

RSTR12，12月相对强势（Relative strength for the last 12 months），属于能量型因子。



### 4.129 RSTR24 

#### 4.129.1 指标含义

RSTR24，24月相对强势（Relative strength for the last 24 months），属于能量型因子。



### 4.130 SalesCostRatio

#### 4.130.1 指标含义

SalesCostRatio，销售成本率（Sales cost ratio），属于盈利能力和收益质量类因子。

#### 4.130.2 计算公式

销售成本率 = 营业成本 / 营业收入



### 4.131 SaleServiceCashToOR

#### 4.131.1 指标含义

SaleServiceCashToOR，销售商品提供劳务收到的现金与营业收入之比（Sale service cash to operating revenues），属于现金流指标因子。

#### 4.131.2 计算公式

SaleServiceCashToOR = 销售商品和提供劳务收到的现金 / 营业收入



### 4.132 SUE

#### 4.132.1 指标含义

SUE，未预期盈余（Standardized unexpected earnings），属于盈利能力和收益质量类因子。

#### 4.132.2 计算公式

未预期盈余 =（最近一年净利润 - 除去最近一年的过往净利润均值）/ 除去最近一年的过往净利润标准差



### 4.133 TaxRatio 

#### 4.133.1 指标含义

TaxRatio，销售税金率（Tax ratio），属于盈利能力和收益质量类因子。

#### 4.133.2 计算公式

销售税金率 = 营业税金及附加 / 营业收入



### *4.134 TOBT*

#### 4.134.1 指标含义

TOBT，超额流动（Liquidity-turnover beta），属于能量型因子。



### 4.135 TotalAssetGrowRate

#### 4.135.1 指标含义

TotalAssetGrowRate，总资产增长率（Total assets growth rate），属于成长能力类因子。

#### 4.135.2 计算公式

总资产增长率 = 今年总资产 / 去年总资产 - 1



### 4.136 TotalAssetsTRate

#### 4.136.1 指标含义

TotalAssetsTRate，总资产周转率（Total assets turnover rate）。

#### 4.136.2 计算公式

总资产周转率 = 营业收入 / 总资产



### 4.137 TotalProfitCostRatio

#### 4.137.1 指标含义

TotalProfitCostRatio，成本费用利润率（Total profit cost ratio），属于盈利能力和收益质量类因子。

#### 4.137.2 计算公式

成本费用利润率 = 利润总额 /（营业成本 + 财务费用 + 销售费用 + 管理费用）



### 4.138 TotalProfitGrowRate

#### 4.138.1 指标含义

TotalProfitGrowRate，利润总额增长率（Total profit growth rate），属于成长能力类因子。

#### 4.138.2 计算公式

利润总额增长率 = 今年利润总额 / 去年利润总额 - 1



### 4.139 VOL

#### 4.139.1 指标含义

VOL，平均换手率（Turnover Rate），属于成交量型因子。



### 4.140 WVAD

#### 4.140.1 指标含义

WVAD，威廉变异离散量（William's variable accumulation distribution），是一种将成交量加权的量价指标，用于测量从开盘价至收盘价期间，买卖双方各自爆发力的程度。属于超买超卖型因子。

#### 4.140.2 计算公式

A = 当天收盘价 － 当天开盘价

B = 当天最高价 － 当天最低价

V = 当天成交金额

C = A / B * V

WVAD = 选定周期内C值的和

#### 4.140.3 应用法则

WVAD指标的设计原理：WVAD以开盘价、收盘价为界，将单个成交日的成交价格分为三个区域，暂称之为高价区、中间价区、低价区。高价区的价格可视为压力，低价区的价格可视为支撑；求上下两区域占当天总波动的百分比，以便测量成交日的成交量中有多少处于此区域。如果高价区的压力较大，将促使VWAD变成负值，代表卖方的实力强大，此时应该卖出持股。如果区域之下的支撑较大，将促使WVAD变成正值，代表买方的实力雄厚，此时应该买进股票。

WVAD正负之间，强弱一线之隔。由于模拟测试所选用的周期相当长，测试结果也以长周期成绩较佳。因此，长期投资者适合使用。

#### 4.140.4 应用法则

① WVAD是测量股价由开盘至收盘期间，多空两方的战斗力平衡。

② WVAD为正值时，代表多方的冲力占优势，当WVAD由负值变成正值的一刹那，为买入点。

③ WVAD为负值时，代表空方的冲力占优势，当WVAD由正值变为负值的一刹那，为卖出点。

④ 当ADX低于±DI时，WVAD指标失去效用。

⑤ WVAD可与EMV指标搭配使用。



### *4.141 REC*

#### 4.141.1 指标含义

REC，分析师推荐评级（Recommended rating score by analyst），属于分析师预期类因子。



### *4.142 DAREC*

#### 4.142.1 指标含义

DAREC，分析师推荐评级变化（Changes of recommended rating score by analyst），相比于60 个交易日前，属于分析师预期类因子。



### *4.143 GREC*

#### 4.143.1 指标含义

GREC，分析师推荐评级变化趋势（Change tendency of recommended rating score by analyst），过去60 个交易日内的DAREC 符号加和。属于分析师预期类因子。



### *4.144 FY12P*

#### 4.144.1 指标含义

FY12P，分析师盈利预测（Forecast earnings by analyst to market values），属于分析师预期类因子。



### *4.145 DAREV*

#### 4.144.1 指标含义

DAREV，分析师盈利预测变化（Changes of forecast earnings by analyst），相比于60个交易日前，属于分析师预期类因子。



### *4.146 GREV*

#### 4.146.1 指标含义

GREV，分析师盈利预测变化趋势（Change tendency of forecast earnings by analyst），过去60个交易日内的DAREV符号加和，属于分析师预期类因子。



### *4.147 SFY12P*

#### 4.147.1 指标含义

SFY12P，分析师营收预测（Forecast sales by analyst to market values），属于分析师预期类因子。



### *4.148 DASREV*

#### 4.148.1 指标含义

DASREV，分析师盈收预测变化（Changes of forecast sales by analyst），相比于60 个交易日前，属于分析师预期类因子。



### *4.149 GSREV*

#### 4.149.1 指标含义

GSREV，分析师盈收预测变化趋势（Change tendency of forecast sales by analyst），过去60 个交易日内的DASREV 符号加和。属于分析师预期类因子。



### *4.150 FSALESG*

#### 4.150.1 指标含义

FSALESG，未来预期盈收增长（Growth of forecast sales），属于分析师预期类因子。



### *4.151 TA2EV*

#### 4.151.1 计算公式

TA2EV，资产总计与企业价值之比（Assets to enterprise value）。属于估值与市值类因子。



### *4.152 CFO2EV*

#### 4.152.1 指标含义

CFO2EV，经营活动产生的现金流量净额与企业价值之比（Cash provided by operations to enterprise value）。属于现金流指标因子。



### 4.153 ACCA

#### 4.153.1 指标含义

ACCA，现金流资产比和资产回报率之差（Cash flow assets ratio minus return on assets），属于现金流指标因子。

#### 4.153.2 计算公式

ACCA =（经营活动产生的金流量净额 - 净利润）/ 总资产



### *4.154 DEGM*

#### 4.154.1 指标含义

DEGM，毛利率增长（Growth rate of gross income ratio），去年同期相比，属于成长能力类因子。

#### 4.154.2 计算公式

毛利率增长 = 今年毛利率 / 去年毛利率 - 1



### *4.155 SUOI*

#### 4.155.1 指标含义

SUOI，未预期毛利（Standardized unexpected gross income），属于盈利能力和收益质量类因子。



### *4.156 EARNMOM*

#### 4.156.1 指标含义

EARNMOM，八季度净利润变化趋势（Change tendency of net profit in the past eight quarters），前8个季度的净利润，如果同比（去年同期）增长记为+1，同比下滑记为-1，再将8 个值相加。属于成长能力类因子。



### *4.157 FiftyTwoWeekHigh*

#### 4.157.1 指标含义

FiftyTwoWeekHigh，当前价格处于过去1年股价的位置（Price level during the pasted 52 weeks），属于超买超卖型因子。



### *4.158 Volatility*

#### 4.158.1指标含义

Volatility，换手率相对波动率（Volatility of daily turnover during the last N days），属于超买超卖型因子。



### *4.159 Skewness*

#### 4.159.1 指标含义

Skewness，股价偏度（Skewness of price during the last N days），过去20个交易日股价的偏度，属于超买超卖型因子。



### 4.160 ILLIQUIDITY 

#### 4.160.1 指标含义

ILLIQUIDITY，收益相对金额比（Daily return to turnover value during the last N days），过去20个交易日收益相对金额的比例。属于超买超卖型因子。



### 4.161 BackwardADJ

#### 4.161.1 指标含义

BackwardADJ，股价向后复权因子，复权是对股价和成交量进行权息修复。属于超买超卖型因子。



### 4.162 MACD（包含DEA、DIFF）

#### 4.162.1 指标含义

MACD，平滑异同移动平均线（Moving Average Convergence Divergence），又称移动平均聚散指标。MACD为计算两条不同程度（长期与短期）的指数平滑移动平均线（EMA）的差离状况来作为判断行情的基础。在绘制的图形上，除了绘制DIF与DEA快慢移动线以外，MACD还要绘制成围绕零轴线波动的柱形图。DEA、DIFF为计算MACD因子的中间变量。MACD、DEA、DIFF，三者均属于趋势型因子。

MACD吸收了移动平均线的优点，运用移动平均线判断买卖时机，在趋势明显时，收效很大。根据移动平均线原理所发展出来的MACD，一方面客服了移动平均线假信号频繁的缺陷，另一方面能够确保移动平均线最大的战果。

#### 4.162.2 计算公式

① 步骤一：分别计算出收市价SHORT日指数平滑移动线与LONG日指数平滑移动平均线，分别几座EMA（SHORT）与EMA（LONG）。

② 步骤二：求这两条指数平滑移动线的差

DIF = EMA（SHORT）- EMA（LONG）

③ 步骤三：计算DIF的MID日指数平滑移动平均，记为DEA.

④ 步骤四：MACD = DIF - DEA

注：参数SHORT设为12；LONG设为26；MID设为9。

MACD是一个中长期趋势的投资技术工具，DIF与DEA形成了两条快慢移动线，买进与卖出信号取决于这两条线的运行趋势和交叉点。

#### 4.162.3 应用法则

① DIF与DEA均为正值，即都在0轴线以上，大势属于多投市场；DIF与DEA均为负值，即都在0轴以下时，大势属于空头市场。

② 在0轴之上，当DIF值向下穿过DEA值时，为卖出信号。

③ 在0轴之下，当DIF值向上穿过DEA值时，为买入信号。

④ 背离信号，当股票曲线的走势向上，而DIF、DEA曲线走势与之背道而驰，则表示大势即将转跌的信号；反之，则表示大势即将出现好转。

⑤ 当DMI中的ADX指示行情处于盘整或者行情幅度太小时，避免采用MACD交易。因为DEA在盘局时，失误率较高，但是如果配合RSI与KD，可以适当弥补此缺点。



