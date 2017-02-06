#ifndef ERRDEF_H
#define ERRDEF_H

namespace PT_QuantPlatform {
	enum PT_ErrorType
	{
		PT_ErrorType_none,						//��

		//��¼
		PT_ErrorType_userError = 1,				//�û������ڻ��û����������
		PT_ErrorType_overLoginNumError,			//��¼������
		PT_ErrorType_notloginyet,               //δ��¼

		//ע��
		PT_ErrorType_userNameAlreadyExists = 5, //�û����Ѵ���
		PT_ErrorType_mobileAlreadyExists,		//�ֻ����Ѵ���
		PT_ErrorType_mailAlreadyExists,			//ע�������Ѵ���
		PT_ErrorType_passIsTooWeak,				//����̫��

		//�������
		PT_ErrorType_serverConnectedError = 10,	//���������Ӵ���
		PT_ErrorType_sendFailed,                //����������ָ��ʧ��
		PT_ErrorType_dbOperationFailed,         //���ݿ��������
		PT_ErrorType_noServerCanbeused,         //û�п��÷�����
		PT_ErrorType_securityCodeMismatch,      //��̬������֤ʧ��
		PT_ErrorType_noPrivilege,               //�޴�Ȩ��
		PT_ErrorType_noTavailableFuction,       //�ݲ�֧�ִ˹���
		PT_ErrorType_loadDynLibraryFailed,      //��̬�����ʧ��

		//���ײ���
		PT_ErrorType_orderNotFound = 200,          //�޴˶���
		PT_ErrorType_finishedOrder,                //�����Ķ���
		PT_ErrorType_breakRule,                    //�Ƿ�����
		PT_ErrorType_notTradingTime,               //�ǽ���ʱ��
		PT_ErrorType_badModifyOrder,               //�Ƿ��ĸĵ�
		PT_ErrorType_notEnoughPosition,            //��λ����
		PT_ErrorType_notEnoughMoney,               //�ʽ���
		PT_ErrorType_sucrityAccountNotAvailable,   //���ʽ�ͨ���쳣
		PT_ErrorType_cancelFailed_canotCancelYet,  //����ʧ�ܣ���ʱ���ܳ���
		PT_ErrorType_cannotselfdeal,               //�����Գɽ�


		//���鲿��
		

		//ϵͳ����
		PT_ErrorType_invalidAargument = 1000,			//�Ƿ��Ĳ���
		PT_ErrorType_invalidSimulationObjectInstance	//�����ģ�⽻��apiʵ��
	};
}
#endif