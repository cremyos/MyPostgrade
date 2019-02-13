import tensorflow as tf
import numpy as nn


BATCH_SIZE = 300
TRAINING_STEPS_COUNT = 1000
learning_rate = 0.01
INPUT = 1
OUTPUT = 4
HIDEN = 10

x_input = tf.placeholder(tf.float32, [None, INPUT], name = 'x_input')
y_Labels = tf.placeholder(tf.int32, [None, OUTPUT], name = 'y_RealOUTPUT')


trainfile = open('trainData.txt', 'r')
testfile = open('testData.txt', 'r')

lines = trainfile.readlines()
linesTest = testfile.readlines()
rows = len(lines)
rowsTest = len(linesTest)

xdata = nn.zeros((rows, 1))
ylabels = nn.zeros((rows, 4))

xdataTest = nn.zeros((rows, 1))
ylabelsTest = nn.zeros((rows, 4))

TempLabels = []

# xdata = []
# ylabels = []
i = 0
for line in lines:
    xdata[i, :] = float(line.split()[2])
    # 将数据转成one-hot类型
    Tempdata = int(line.split()[3])
    if Tempdata == 0:
        TempLabels.append([1, 0, 0, 0])
    elif Tempdata == 1:
        TempLabels.append([0, 1, 0, 0])
    elif Tempdata == 2:
        TempLabels.append([0, 0, 1, 0])
    else:
        TempLabels.append([0, 0, 0, 1])
    i = i+1


ylabels = TempLabels
trainfile.close()

TempTestLabels = []
i = 0
for lineTest in linesTest:
    xdataTest[i, :] = float(lineTest.split()[2])
    # ylabelsTest[i, :] = int(lineTest.split()[3])
    Tempdata = int(line.split()[3])
    if Tempdata == 0:
        TempTestLabels.append([1, 0, 0, 0])
    elif Tempdata == 1:
        TempTestLabels.append([0, 1, 0, 0])
    elif Tempdata == 2:
        TempTestLabels.append([0, 0, 1, 0])
    else:
        TempTestLabels.append([0, 0, 0, 1])
    i = i+1


ylabelsTest = TempTestLabels

print(ylabels)


print(ylabelsTest)




# get_varibale 创建一个新的变量，如果变量为定义，则创建一个新的；如果定义了，则直接获取
with tf.variable_scope('First_Layer'):
    weight1 = tf.get_variable("weight1", [INPUT, HIDEN], initializer = tf.truncated_normal_initializer(stddev = 0.1))
    biases1 = tf.get_variable("bias1", [1, HIDEN], initializer = tf.constant_initializer(0.1))

    fc1 = tf.nn.relu(tf.matmul(x_input, weight1) + biases1)
    fc1 = tf.nn.dropout(fc1, 0.5)

with tf.variable_scope('Second_Layer'):
    weight2 = tf.get_variable("weight2", [HIDEN, OUTPUT], initializer=tf.truncated_normal_initializer(stddev=0.1))
    biases2 = tf.get_variable("bias2", [1, OUTPUT], initializer=tf.constant_initializer(0.1))
    logit = tf.matmul(fc1, weight2) + biases2

# global_step = tf.Variable(0, trainable=False)
# sparse_softmax_cross_entropy_with_logits中 lables接受直接的数字标签
# 如[1], [2], [3], [4] （类型只能为int32，int64）
# 而softmax_cross_entropy_with_logits中 labels接受one-hot标签
# 如[1,0,0,0], [0,1,0,0],[0,0,1,0], [0,0,0,1] （类型为int32， int64）
prediction = tf.nn.softmax(logit)
# cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logit, labels=tf.argmax(y_Labels, 1))
cross_entropy = tf.nn.softmax_cross_entropy_with_logits(logits=logit, labels=y_Labels)
cost = tf.reduce_mean(cross_entropy)
accuracy = tf.equal(tf.arg_max(prediction, 1), tf.arg_max(y_Labels, 1))
acc = tf.reduce_mean(tf.cast(accuracy, 'float'))
# loss = tf.reduce_mean(tf.reduce_sum(tf.square(y_Labels - prediction), reduction_indices=[1]))
# train_step = tf.train.AdamOptimizer(0.1).minimize(loss)

# cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logit, labels=tf.argmax(y_Labels))
# cross_entropy_mean = tf.reduce_mean(cross_entropy)
# loss = cross_entropy_mean

# train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(loss, global_step = global_step)

with tf.Session() as sess:
    tf.global_variables_initializer().run()
    for i32Step in range(TRAINING_STEPS_COUNT):
        # trainStep = sess.run(train_step, feed_dict={x_input: xdata, y_Labels: ylabels})
        # TrainLoss = sess.run(loss, feed_dict={x_input: xdata, y_Labels: ylabels})
        # TrainPrrediction = sess.run(prediction, feed_dict={x_input: xdata, y_Labels: ylabels})
        traincost = sess.run(cost, feed_dict={x_input: xdata, y_Labels: ylabels})
        if i32Step % 100 == 0:
            ACC = sess.run(acc, feed_dict={x_input: xdata, y_Labels: ylabels})
            print("i32Step = ", i32Step)
            print("cost = ", traincost)
            print("ACCURACY = ", ACC)


    logitTest = sess.run(logit, feed_dict={x_input: xdataTest, y_Labels: ylabelsTest})
    print("logitTest  = ", logitTest)
    PreTest = nn.argmax(logitTest, 1)
    print("predict = ", PreTest)
#
# #



