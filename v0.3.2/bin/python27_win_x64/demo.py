# -*- coding: utf-8 -*-
from PT_QuantBaseApi import GetDataCallBack, GetDataApi, SimulationGetDataApi, TradeDataCallBack, TradeDataApi, SimulationTradeDataApi

class TradeCallBack(TradeDataCallBack):
	def __init__(self):
		super(TradeCallBack, self).__init__()
	#重载回调
	def OnRspUserTradeInfo(self, userInfo):
		#print("OnRspUserTradeInfo:", userInfo)
		pass
	def OnRspOrderInsert(self, rsp, err):
		print("OnRspOrderInsert:", rsp, err)
		pass
	def OnRspOrderModify(self, rsp, err):
		#print("OnRspOrderModify:", rsp, err)
		pass
	def OnRspOrderDelete(self):
		#print("OnRspOrderDelete:", rsp, err)
		pass
	def OnRspQryOrder(self, rsp, err, isEnd):
		#print("OnRspQryOrder:", rsp, err, isEnd)
		pass
	def OnRspQryMatch(self, rsp, err, isEnd):
		#print("OnRspQryMatch:", rsp, err, isEnd)
		pass
	def OnRspQryPosition(self, rsp, err, isEnd):
		#print("OnRspQryPosition:", rsp, err, isEnd)
		pass
	def OnRspQryCapitalAccount(self, rsp, err, isEnd):
		#print("OnRspQryCapitalAccount:", rsp, err, isEnd)
		pass
	def OnRspQrySecuDebt(self, rsp, err, isEnd):
		#print("OnRspQrySecuDebt:", rsp, err, isEnd)
		pass
	def OnRspQryMaxEntrustCount(self, rsp, err, isEnd):
		#print("OnRspQryMaxEntrustCount:", rsp, err, isEnd)
		pass
	def OnRspQrySecuritiesLendingAmount(self, rsp, err, isEnd):
		#print("OnRspQrySecuritiesLendingAmount:", rsp, err, isEnd)
		pass
	def OnRtnOrderStatusChangeNotice(self, rtn):
		print("OnRtnOrderStatusChangeNotice:", rtn)
		pass
	def OnRtnOrderMatchNotice(self, rtn):
		print("OnRtnOrderMatchNotice:", rtn)
		pass
		

class DataCallBack(GetDataCallBack):
	def __init__(self, tApi):
		super(DataCallBack, self).__init__()
		self.tApi = tApi
		self.MA = 0
		self.down = False
		self.up = False
	def SetEMA(self, ma):
		self.MA = ma
		pass
	def getMA(self, price):
		return (self.MA*4 + price)/5
	#重载回调
	def OnRecvCodes(self, codes, optionCodes):
		#print("OnRecvCodes: ",codes, optionCodes)
		pass
	def OnRecvDayBegin(self, dateStr):
		print("OnRecvDayBegin: ", dateStr)
		pass
	def OnRecvMarket(self, market):
		#print("OnRecvMarket", market["szDatetime"],  market["nMatch"], self.getMA(market["nMatch"]), market["nOpen"])
		if market["nMatch"] < self.getMA(market["nMatch"]):
			self.down = True
			#print("down", market["szDatetime"],  market["nMatch"], self.getMA(market["nMatch"]))
			pass
		if self.down and (market["nMatch"] >= self.getMA(market["nMatch"])):
			if not self.up:
				print("up", market["szDatetime"],  market["nMatch"], self.getMA(market["nMatch"]))
				newOrderReq = {
					"nOrderPrice": market["nBidPrice"][0] + 0.01,
					"nOrderVol": 100,
					"szContractCode":market["szWindCode"],
					"nTradeType": 100,
					"nAccountId": 0,
					"nUserId" : 1,
					"nUserInt" : 0,
					"nUserDouble" : 0,
					"szUserStr" :""
				}
				self.tApi.OrderInsert(newOrderReq)
				pass
			self.up = True
			pass
		"""
		if market["szWindCode"] == "600000.SH":
			
		"""
		#print("OnRecvMarket: ", market)
		pass
	def OnRecvTransaction(self, transaction):
		#print("OnRecvTransaction: ", transaction)
		pass
	def OnRecvDayEnd(self, dateStr):
		print("OnRecvDayEnd: ", dateStr)
		pass
	def OnRecvKLine(self, kLine):
		#print("OnRecvKLine: ", kLine)
		pass
	def OnRecvOver(self):
		print("OnRecvOver")
		pass
		


def main():
	tspi = TradeDataCallBack()
	t = SimulationTradeDataApi(tspi)

	mspi = DataCallBack(t);
	mapi = SimulationGetDataApi(mspi, t, True, 3000);

	mapi.Login("CYF","CYF")
	t.Login("CYF", "CYF")

	dayLineList = mapi.GetDayKline("000782.SZ", "2016-12-01", "2016-12-23")
	MAList = []

	factors = mapi.GetStockFactors("000782.SZ", ["EMA5"], "2016-12-01", "2016-12-23");
	for x in factors:
		MAList.append(x["mFactors"]["EMA5"])
		pass
	MA = (MAList[-1] + MAList[-2] + MAList[-3] + MAList[-4])/4

	#print(factors)
	#print(MAList, MA)

	mspi.SetEMA(MA)


	#mapi.ReqRealtimeData(["000782.SZ"], False, 93000000)
	#mapi.ReqHistoryData("2016-01-01 9:30:00", "2016-12-01 24:00:00", ["000782.SZ"], False)
	mapi.ReqKline("minute","2016-01-01 9:30:00", "2016-12-01 24:00:00", ["000782.SZ"], False)



	while True:
		#time.sleep(15)
		#x, y = t.OrderInsert(newOrderReq)
		pass


"""
	


	mspi = DataCallBack(t);
	m = SimulationGetDataApi(mspi, t, True, 3000)
	m.Login("CYF", "CYF")
	t.Login("CYF", "CYF")

	#print(dir(t))
	#print(dir(m))

	stockInfo = m.GetStockBaseInfo("600000.SH","","");
	print(stockInfo)

	kLine = m.GetDayKline("600000.SH","2016-05-01", "2016-05-10");
	print(kLine)

	factors = m.GetStockFactors("600000.SH", ["AR","MACD"], "2016-05-01", "2016-05-10");
	print(factors)


	#m.ReqHistoryData("2016-05-03 9:30:00", "2016-05-03 9:30:10", ["600000.SH"], False)
	
"""
"""
	newOrderReq = {
		"nOrderPrice": 12.5,
		"nOrderVol": 100,
		"szContractCode":"600000.SH",
		"nTradeType": 100,
		"nAccountId": 1,
		"nUserId" : 1,
		"nUserInt" : 0,
		"nUserDouble" : 0,
		"szUserStr" :""
	}
"""

	#x, y = t.OrderInsert(newOrderReq)
#	print(dir(newOrderReq))
#	reqId, err = t.OrderInsert(newOrderReq)
#	print(newOrderReq.length, reqId, err)

if __name__ == '__main__':
	main()