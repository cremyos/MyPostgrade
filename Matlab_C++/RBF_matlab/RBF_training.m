function [ W, sigma, C ] = RBF_training( data, label, n_center_vec )
% 自组织选取中心的方法
%RBF_TRAINING Summary of this function goes here
%   Detailed explanation goes here

    % Using kmeans to find cinter vector
    rng(1);
    [idx, C] = kmeans(data, n_center_vec);

    %学习率
%     alpha = 0.01;
%     count = 1;
%     maxcount = 1;
%     while (count<=maxcount) %结束条件1迭代1000次 
        % Calulate sigma 
        n_data = size(data,1);

        % calculate K
        K = zeros(n_center_vec, 1);
        for i=1:n_center_vec
            K(i) = numel(find(idx == i));
        end

        % Using knnsearch to find K nearest neighbor points for each center vector
        % then calucate sigma
        sigma = zeros(n_center_vec, 1);
        for i=1:n_center_vec
            [n] = knnsearch(data, C(i,:), 'k', K(i));
            L2 = (bsxfun(@minus, data(n,:), C(i,:)).^2);
            L2 = sum(L2(:));
            sigma(i) = sqrt(1/K(i)*L2);
        end

        sigma = sigma + 0.01;
        % Calutate weights
        % kernel matrix
        k_mat = zeros(n_data, n_center_vec);

        for i=1:n_center_vec
            r = bsxfun(@minus, data, C(i,:)).^2;
            r = sum(r,2);
            k_mat(:,i) = exp((-r.^2)/(2*sigma(i)^2));
        end

        W = pinv(k_mat'*k_mat)*k_mat'*label;
%         W
%         
%         y_out = k_mat * W;
%         
%         [dataline, datarow] = size(data);
%         e = zeros(n_center_vec, 1);
%         %求误差
%         for j = 1:dataline
%             i32TempIndex = label(j, :) + 1;
%             e(i32TempIndex, :) = e(i32TempIndex, :) + (data(j, :) - y_out(j, :));
%         end       
%         
% %         size(k_mat)
% %         size(e)
% %         size(W)
%         
%         for i = 1:n_center_vec
%             for j = 1:dataline                
%                 W(i, :) = W(i, :) - alpha * k_mat(j, i) * e(i, :);
%             end
%         end
%         W
%         
%         C
%         
%         count = count + 1;
%     end
        
%     W = inv(k_mat'*k_mat)*k_mat'*label;
end     