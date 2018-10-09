[ReadClass, ReadData, ReadLabels] = textread('DataFile.txt','%d %f %d');
[ReadDataHang, ReadDataLie] = size(ReadData);
ReadDataHangTrain = round(ReadDataHang * 0.5);

% 获取训练数据
TrainClass = ReadClass(1:ReadDataHangTrain, 1);
TrainData = ReadData(1:ReadDataHangTrain, 1);
TrainClass = [];
Data1 = [];
Data2 = [];
Data3 = [];
Data4 = [];
j = 1;
for i = 1:ReadDataHangTrain
    if ReadLabels(i, 1) == 0
        TrainClass(j,:) = [1, 0, 0, 0];
        Data1(j, :) = ReadData(i, 1);
        Data2(j, :) = -99;
        Data3(j, :) = -99;
        Data4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 1
        TrainClass(j,:) = [0, 1, 0, 0];
        Data2(j, :) = ReadData(i, 1);
        Data1(j, :) = -99;
        Data3(j, :) = -99;
        Data4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 2
        TrainClass(j,:) = [0, 0, 1, 0];
        Data1(j, :) = -99;
        Data2(j, :) = -99;
        Data3(j, :) = ReadData(i, 1);
        Data4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 3
        TrainClass(j,:) = [0, 0, 0, 1];
        Data1(j, :) = -99;
        Data2(j, :) = -99;
        Data3(j, :) = -99;
        Data4(j, :) = ReadData(i, 1);        
    end
    j = j + 1;
end
TrainData = [Data1, Data2, Data3, Data4];

% TrainLabels = ReadLabels(1:ReadDataHangTrain, 1);
TrainLabels = TrainClass;
TrainMap = [TrainClass, TrainData, TrainLabels];
% TrainDatasize = size(TrainData)

% 获取测试数据
TestClass = ReadClass(ReadDataHangTrain:ReadDataHang - 1, 1);
% TestData = ReadData(ReadDataHangTrain:ReadDataHang - 1, 1);
TestClass = [];
testData1 = [];
testData2 = [];
testData3 = [];
testData4 = [];
j = 1;

for i = ReadDataHangTrain:ReadDataHang - 1
    if ReadLabels(i, 1) == 0
        TestClass(j,:) = [1, 0, 0, 0];   
        testData1(j, :) = ReadData(i, 1);
        testData2(j, :) = -99;
        testData3(j, :) = -99;
        testData4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 1
        TestClass(j,:) = [0, 1, 0, 0];  
        testData2(j, :) = ReadData(i, 1);
        testData1(j, :) = -99;
        testData3(j, :) = -99;
        testData4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 2
        TestClass(j,:) = [0, 0, 1, 0];
        testData1(j, :) = -99;
        testData2(j, :) = -99;
        testData3(j, :) = ReadData(i, 1);
        testData4(j, :) = -99;
        
    elseif ReadLabels(i, 1) == 3
        TestClass(j,:) = [0, 0, 0, 1];
        testData1(j, :) = -99;
        testData2(j, :) = -99;
        testData3(j, :) = -99;
        testData4(j, :) = ReadData(i, 1);  
    end
    j = j + 1;
end
% TestLabels = ReadLabels(ReadDataHangTrain:ReadDataHang - 1, 1);
TestLabels = TestClass;
TestData = [testData1, testData2, testData3, testData4];
TestMap = [TestClass, TestData, TestLabels];
% TestDatasize = size(TestData)

[MMM, NNN] = size(TrainData)
[M_M, N_N] = size(TrainLabels)

%% 训练过程
% rbf = newrb(TrainData, TrainLabels, 0.1, 5, 6, 5);
% rbf = newrb(TrainData, TrainLabels);
rbf = newrbe(TrainData, TrainLabels);
Y_OutRealPut = rbf(TrainData);
[TrainLabelsLine, TrainLabelsRow] = size(TrainLabels);
[RealLine, RealRow] = size(Y_OutRealPut);
Y_OutPut = round(Y_OutRealPut);

% 训练数据准确性分析
correctTrain = Y_OutPut - TrainLabels;


% 求矩阵非零元素的个数
correctTrain_Count = nnz(correctTrain);
[hang, lie] = size(correctTrain);
AccuracyTrain = 1 - correctTrain_Count/hang


%% ++++

%% 
Y_TestOutPut = rbf(TestData);
% Y_TestOutPut = trainedClassifier(TestMap)
% Y_TestRealOutPut = sim(rbf, TestData);
Y_TestRealOutPut = round(Y_TestOutPut);
[TestLabelsLine, TestLabelsRow] = size(TestLabels);
[RealTestLine, RealTestRow] = size(Y_TestRealOutPut);

% 训练数据准确性分析
correctTest = Y_TestRealOutPut - TestLabels;


% 求矩阵非零元素的个数
correctTest_Count = nnz(correctTest);
[Testhang, Testlie] = size(correctTest);
AccuracyTest = 1 - correctTest_Count/Testhang





