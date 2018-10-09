% ��ȡ����
% [ReadDataT,ReadLabelsT] = textread('DataFile.txt','%f %d');
% [ReadClass, ReadInfoNum, ReadData, ReadLabels] = textread('DataInputNetFile.csv','%d %d %f %d');
ReadClass = DataInputNetFile(:, 1);
ReadInfoNum = DataInputNetFile(:, 2);
ReadData = DataInputNetFile(:, 3);
ReadLabels = DataInputNetFile(:, 4);
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




%% training function and predict function
% ѵ�����ݣ�ռ80%
[W1, sigma1, C1] = RBF_training(TrainData, TrainLabels, 4);
y1 = RBF_predict(TrainData, W1, sigma1, C1);
Y_OutPut = round(y1);
% ѵ������׼ȷ�Է���
correctTrain = Y_OutPut - TrainLabels;

% ��������Ԫ�صĸ���
correctTrain_Count = nnz(correctTrain);
[hang, lie] = size(correctTrain);

% ��׼ȷ��
AccuracyTrain = 1 - correctTrain_Count/hang

[PrintHang,PrintLie] = size(TrainData);

%���������ļ���
fidout=fopen('OutPut20181009Train.txt','w');
% ����������У��Ѵ�������д���ļ�OutPut.txt
%fprintf(fidout, '%f %d || %d\n', TestData, TestLabels, yReal_OutPut);
for i = 1:PrintHang
    fprintf(fidout, '%d	%d %f %d %d\n', TrainClass(i, PrintLie), ReadInfoNum(i, PrintLie), TrainData(i, PrintLie), TrainLabels(i, PrintLie), Y_OutPut(i, PrintLie));
end
fclose(fidout);

% %% ��������
% [x_Line, y_Row] = size(TrainData);
% X_plot = []
% X_plot = 1:50;
% % xx = linspace(1, 3000);
% % yy1 = spline(X_plot, yReal_OutPut, xx)
% % yy2 = spline(X_plot, TestLabels, xx)
% plot(X_plot, Y_OutPut(1:500), '*', X_plot, TrainLabels(1:500), 'o');
% hold on
% % plot(xx, yy1, 'r', xx, yy2, 'g');
%%


yTest = RBF_predict(TestData, W1, sigma1, C1);
yReal_OutPut = round(yTest);
% ��������׼ȷ�Է���
correctTest = yReal_OutPut - TestLabels;

% ��������Ԫ�صĸ���
correctTest_Count = nnz(correctTest);
[hang, lie] = size(correctTest);



% ��׼ȷ��
AccuracyTest = 1 - correctTest_Count/hang

[PrintTestHang, PrintTestLie] = size(TestData);

%���������ļ���
fidout=fopen('OutPut20181009Test.txt','w');
% ����������У��Ѵ�������д���ļ�OutPut.txt
%fprintf(fidout, '%f %d || %d\n', TestData, TestLabels, yReal_OutPut);
for i = 1:PrintTestHang
    fprintf(fidout, '%d %d %f %d %d\n', TestClass(i, PrintTestLie), TestInfoNum(i, PrintTestLie), TestData(i, PrintTestLie), TestLabels(i, PrintTestLie), yReal_OutPut(i, PrintTestLie));
end
fclose(fidout);

% ���
%���������ļ���
%fidout=fopen('OutPutWrong3.txt','w');
% ����������У��Ѵ�������д���ļ�OutPut.txt
%fprintf(fidout, '%f %d\n', TrainFile(1:37988, 1), TrainFile(1:37988, 2));
%fprintf(fidout, '%f %d\n', ReadData, ReadLabels);
%fclose(fidout);
