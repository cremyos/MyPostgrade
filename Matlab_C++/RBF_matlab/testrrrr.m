%%  
% 根据以下链接中的思想，把C++代码改写成M文件  
% http://www.cnblogs.com/zhangchaoyang/articles/2591663.html  
clear;clc;  
P=101;%训练样本共P个  
X=[]; %训练输入  
Y=[]; %训练输出  
M=10; %数据中心的个数（或说隐藏层的个数）  
  
  
centers=[];%存储数据中心（或说核函数的个数）  
deltas=[]; %存储核函数的标准差  
weights=[];%存放网络的权值（或说每个核的权值）  
set = {};  %存放不同簇所包含的所有样例  
gap=0.1;   %这是用k_means法进行聚类的时候的停止规则  
%**************************************************************************  
%构造训练样本X,Y  
X=[-4:0.08:4];  
for i=1:P  
    Y(i)=1.1*(1-X(i)+2*X(i)^2)*exp(-X(i)^2/2);  
end  
Y=Y+0.1*randn(1,P);  
%%  
%**************************************************************************  
%对输入进行聚类，(获得核函数的中心)  
for i=1:M   
    %因为我们的X是均匀分布,所以初始化也为均匀的  
    centers(i)= X( i*floor( P/10 ) );  
end  
done=0;  
while(~done)  
    for i=1:M  
       set{i}=[];  
    end  
    %计算P中每个点所属的簇  
    for i=1:P  
        distance=100;%设置一个比较大的值  
        for j=1:M  
            curr=abs(X(i)-centers(j));  
            if curr<distance  
                sets=j;  
                distance=curr;  
            end  
        end  
        set{sets}=[set{sets},X(i)];%把新分类的样例添到相应的簇中  
    end  
    %重新计算每个簇的质心  
    for i=1:M  
        new_centers(i)=sum(set{i})/length(set{i});  
    end  
    %根据各簇中心的更新情况决定是否已完成循环  
    done=0;  
%     abs(centers-new_centers)  
    for i=1:M  
        if abs(centers(i)-new_centers(i))>gap  
            done=0;  
            break;  
        else  
            done=1;  
        end  
    end  
    centers=new_centers;  
end  
%计算出每个高斯核函数的标准差（重叠系数=1）  
for i=1:M  
    curr=abs( centers-centers(i) );  
    [curr_2,b]=min(curr);  
    curr(b)=100;  
    curr_2=min(curr);  
    deltas(i)=1*curr_2;  
end  
%**************************************************************************  
%根据d=sum(K*W)  
%首先构造K为P×M的  
for i=1:P  
    for j=1:M  
        curr=abs(X(i)-centers(j));  
        K(i,j)=exp( -curr^2/(2*deltas(j)^2) );  
    end  
end  
%计算权值矩阵  
weights=inv(K'*K)*K'*Y';  
%**************************************************************************  
%测试计算出函数的情况  
x_test=[-4:0.1:4];  
for i=1:length(x_test)  
    sum=0;  
    for j=1:M  
        curr=weights(j)*exp(-abs(x_test(i)-centers(j))^2/(2*deltas(j)^2));  
        sum=sum+curr;  
    end  
    y_test(i)=sum;  
end  
figure(1)  
scatter(X,Y,'k+');  
hold on;  
plot(x_test,y_test,'r.-')