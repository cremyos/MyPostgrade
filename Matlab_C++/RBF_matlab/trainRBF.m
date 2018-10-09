function [rbf] = trainRBF(rbf, train_x, train_y)
	%%% step 1: calculate gradient
	numSamples = size(train_x, 2);
	Green = zeros(rbf.hiddenSize, 1);
	output = zeros(rbf.outputSize, 1);
	delta_weight = zeros(rbf.outputSize, rbf.hiddenSize);
	delta_center = zeros(rbf.inputSize, rbf.hiddenSize);
	delta_delta =  zeros(1, rbf.hiddenSize);
	rbf.cost = 0;
	for i = 1 : numSamples
		%% Feed forward
		for j = 1 : rbf.hiddenSize
			Green(j, 1) = green(train_x(:, i), rbf.center(:, j), rbf.delta(j));
		end	
		output = rbf.weight * Green;	
		
		%% Back propagation
		delta3 = -(train_y(:, i) - output);
		rbf.cost = rbf.cost + sum(delta3.^2);
		delta_weight = delta_weight + delta3 * Green';
		delta2 = rbf.weight' * delta3 .* Green;
		for j = 1 : rbf.hiddenSize
			delta_center(:, j) = delta_center(:, j) + delta2(j) .* (train_x(:, i) - rbf.center(:, j)) ./ rbf.delta(j)^2;
			delta_delta(j) = delta_delta(j)+ delta2(j) * sum((train_x(:, i) - rbf.center(:, j)).^2) ./ rbf.delta(j)^3;
		end
	end
 
	%%% step 2: update parameters
	rbf.cost = 0.5 * rbf.cost ./ numSamples;
	rbf.weight = rbf.weight - rbf.alpha .* delta_weight ./ numSamples;
	rbf.center = rbf.center - rbf.alpha .* delta_center ./ numSamples;
	rbf.delta = rbf.delta - rbf.alpha .* delta_delta ./ numSamples;
end