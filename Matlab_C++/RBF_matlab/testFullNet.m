[ReadDataHang, ReadDataLie] = size(ReadData);
ReadDataHangTrain = round(ReadDataHang * 0.8)

% ��ȡѵ������
TrainClass = ReadClass(1:ReadDataHangTrain, 1);
TrainData = ReadData(1:ReadDataHangTrain, 1);
% TrainData = TrainData + 100;
TrainLabels = ReadLabels(1:ReadDataHangTrain, 1);

% ��ȡ��������
TestClass = ReadClass(ReadDataHangTrain:ReadDataHang, 1);
TestInfoNum = ReadInfoNum(ReadDataHangTrain:ReadDataHang, 1);
TestData = ReadData(ReadDataHangTrain:ReadDataHang, 1);
TestLabels = ReadLabels(ReadDataHangTrain:ReadDataHang, 1);
 
%ѵ��������
net=newff(minmax(TrainData),[5,1],{'tansig','purelin'},'traingdm'); 
net.trainParam.epochs=1000;
net.trainParam.lr=0.1;
net.trainParam.goal=0.0000004;
[net,tr]=train(net, TrainData, TrainClass)
Y=sim(net, TestData)
 
%���������������
% TestLabels(find(TestLabels>0.5))=1%ͨ���߼�����ֵ1������0.5��λ��
% TestLabels(find(TestLabels<=0.5))=0
% Y(find(Y>0.5))=1
% Y(find(Y<=0.5))=0
C=TestLabels - Y %�������������һ����λ��Ϊ1��-1
error=sum(abs(C))/length(C)%ȡ����ֵ��͵õ����������������Բ����������õ�������