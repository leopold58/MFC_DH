//		PLU����DLL��
//
//	ͨ��һ��Dhset.exe���úõ�ini�ļ�
//	������PLU����
//				Roya	07.4.9
#ifdef	DHSPN_EXPORTS
#define DHSPN __declspec(dllexport)
#else
#define DHSPN __declspec(dllimport)
#endif


//	����ֵ˵��
//	0	�ɹ�
//	-1	dhip.iniΪ�ջ������ô���
//	-2	dhpluversion.intΪ�ջ����ô���
//	-3	dhplupathname.iniΪ�ջ����ô���
//	-4	dhplupathname.ini�ж�ȡ��Plu·������,��ָ���Plu�ļ�������
//	-5	Plu�ı�Ϊ�ջ������ô���(��:Plu�汾��Plu�ı����ݲ�һ�µ�)
//	-6	ͨ���д����쳣,�鿴������Ϣ���ȡReturn.txt;

//	Return.txt�о����쳣���˵��
//	0	�ɹ�
//	-1	����ʧ��
//	-2	���ͺ�,δ�յ�������Ϣ
//	-3	��������ʧ��
//	-4	ip��ַת��ʧ��
//	-10	���ͺ�δ�յ���ȷ������Ϣ(0d,0a,03������־)

DHSPN	int WINAPI	dhSendPluDefault();
DHSPN	int WINAPI	dhRcvRdDefault();