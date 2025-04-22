import numpy as np

epsilon = 0.000001

def step_func(t):
    if t > epsilon: 
        return 1
    else:
        return 0

X = np.array([[0, 0, 1],[0, 1, 1],[1, 0, 1],
            [1, 1, 1]])

y = np.array([0, 1, 1, 0])

W = np.zeros(len(X[0]))
print(W)

def perceptron_fit(X, Y, epochs=100):
    global W

    eta = 0.2 # 학습률
    
    for t in range(epochs):

        print("epoch=", t, "==================")
        for i in range(len(X)):

            predict = step_func(np.dot(X[i],W))
            error =  Y[i] - predict
            print("변경전 가중치 = ",W)
            print("error=", error)
            print("X[i] = ",X[i])
            #W += eta * error * X[i]
            Wx = eta * error * X[i]
            #print("변경할 가중치 = ", Wx)
            W = W+Wx

            print("현재 처리 입력=",X[i], "정답=",Y[i], "predict=", predict,"변형된 가중치=",W)
        print("====================")

perceptron_fit(X, y, 1000)