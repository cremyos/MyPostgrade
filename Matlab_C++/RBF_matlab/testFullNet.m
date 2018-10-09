[ReadDataHang, ReadDataLie] = size(ReadData);
ReadDataHangTrain = round(ReadDataHang * 0.8)

% 获取训练数据
TrainClass = ReadClass(1:ReadDataHangTrain, 1);
TrainData = ReadData(1:ReadDataHangTrain, 1);
% TrainData = TrainData + 100;
TrainLabels = ReadLabels(1:ReadDataHangTrain, 1);

% 获取测试数据
TestClass = ReadClass(ReadDataHangTrain:ReadDataHang, 1);
TestInfoNum = ReadInfoNum(ReadDataHangTrain:ReadDataHang, 1);
TestData = ReadData(ReadDataHangTrain:ReadDataHang, 1);
TestLabels = ReadLabels(ReadDataHangTrain:ReadDataHang, 1);
 
%训练神经网络
net=newff(minmax(TrainData),[5,1],{'tansig','purelin'},'traingdm'); 
net.trainParam.epochs=1000;
net.trainParam.lr=0.1;
net.trainParam.goal=0.0000004;
[net,tr]=train(net, TrainData, TrainClass)
Y=sim(net, TestData)
 
%计算神经网络错误率
% TestLabels(find(TestLabels>0.5))=1%通过逻辑矩阵赋值1给大于0.5的位置
% TestLabels(find(TestLabels<=0.5))=0
% Y(find(Y>0.5))=1
% Y(find(Y<=0.5))=0
C=TestLabels - Y %俩矩阵相减，不一样的位置为1或-1
error=sum(abs(C))/length(C)%取绝对值求和得到错误样本数，除以测试样本数得到错误率