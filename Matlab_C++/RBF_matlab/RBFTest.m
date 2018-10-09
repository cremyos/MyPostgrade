% 读取数据
% [ReadDataT,ReadLabelsT] = textread('DataFile.txt','%f %d');
% [ReadClass, ReadInfoNum, ReadData, ReadLabels] = textread('DataInputNetFile.csv','%d %d %f %d');
ReadClass = DataInputNetFile(:, 1);
ReadInfoNum = DataInputNetFile(:, 2);
ReadData = DataInputNetFile(:, 3);
ReadLabels = DataInputNetFile(:, 4);
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




%% training function and predict function
% 训练数据，占80%
[W1, sigma1, C1] = RBF_training(TrainData, TrainLabels, 4);
y1 = RBF_predict(TrainData, W1, sigma1, C1);
Y_OutPut = round(y1);
% 训练数据准确性分析
correctTrain = Y_OutPut - TrainLabels;

% 求矩阵非零元素的个数
correctTrain_Count = nnz(correctTrain);
[hang, lie] = size(correctTrain);

% 求准确率
AccuracyTrain = 1 - correctTrain_Count/hang

[PrintHang,PrintLie] = size(TrainData);

%保存结果到文件中
fidout=fopen('OutPut20181009Train.txt','w');
% 如果是数字行，把此行数据写入文件OutPut.txt
%fprintf(fidout, '%f %d || %d\n', TestData, TestLabels, yReal_OutPut);
for i = 1:PrintHang
    fprintf(fidout, '%d	%d %f %d %d\n', TrainClass(i, PrintLie), ReadInfoNum(i, PrintLie), TrainData(i, PrintLie), TrainLabels(i, PrintLie), Y_OutPut(i, PrintLie));
end
fclose(fidout);

% %% 绘制曲线
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
% 测试数据准确性分析
correctTest = yReal_OutPut - TestLabels;

% 求矩阵非零元素的个数
correctTest_Count = nnz(correctTest);
[hang, lie] = size(correctTest);



% 求准确率
AccuracyTest = 1 - correctTest_Count/hang

[PrintTestHang, PrintTestLie] = size(TestData);

%保存结果到文件中
fidout=fopen('OutPut20181009Test.txt','w');
% 如果是数字行，把此行数据写入文件OutPut.txt
%fprintf(fidout, '%f %d || %d\n', TestData, TestLabels, yReal_OutPut);
for i = 1:PrintTestHang
    fprintf(fidout, '%d %d %f %d %d\n', TestClass(i, PrintTestLie), TestInfoNum(i, PrintTestLie), TestData(i, PrintTestLie), TestLabels(i, PrintTestLie), yReal_OutPut(i, PrintTestLie));
end
fclose(fidout);

% 查错
%保存结果到文件中
%fidout=fopen('OutPutWrong3.txt','w');
% 如果是数字行，把此行数据写入文件OutPut.txt
%fprintf(fidout, '%f %d\n', TrainFile(1:37988, 1), TrainFile(1:37988, 2));
%fprintf(fidout, '%f %d\n', ReadData, ReadLabels);
%fclose(fidout);
