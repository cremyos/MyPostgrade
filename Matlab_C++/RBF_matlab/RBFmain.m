clear;
load sample_ex6.mat;
[M,N]=size(data);
hidden_layers=10;
theta=0.01;
eta=0.01;
wkj=-1/(hidden_layers^0.5)+2/(hidden_layers^0.5)*rand(1,hidden_layers);
sigma=zeros(1,hidden_layers);
for i=1:hidden_layers
    sigma(1,i)=2+2*rand();   %initialize sigma to 2.0-4.0
end
%input data normalization
% [norm_data,norm_dataps]=mapminmax(data);

%10-fold crossing validation
sub_N=N/10;
rates=zeros(1,10);
for i=1:10
    testdata=data(:,1:sub_N);  %set the first part as testdata 
    traindata=data(:,sub_N+1:N);   %set the next nine part as traindata
    center_points=zeros(hidden_layers,M-1);
    for j=1:10
        %random initialize center points in train data
        center_points(j,:)=traindata(1:2,ceil(rand()*size(traindata,2)))';
    end
    rates(1,i)=Batch_RBF_Neural_Network(traindata,testdata,hidden_layers,wkj,center_points,sigma,theta,eta);
    data=[traindata,testdata];
end
disp('the accuracy of ten validation:')
disp(rates);disp('the average accuracy is:')
ave_rate=sum(rates)/10;
disp(ave_rate);
