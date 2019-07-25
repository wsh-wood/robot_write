import torch
import torch.nn as nn
import torch.optim as optim
from data import getData
from module import Cnn

model = Cnn(1, 10)
train_loader, test_loader = getData()
epochs = 10  # 训练次数
lr = 0.001  # 学习率
momentum = 0.6  # 动量
model_file = '/home/xy/CLionProjects/robot_write/MnistCNN/models'


def train_and_test(model, train_loader, test_loader, epochs
                   , lr, momentum):
    # 优化算法用SGD，损失函数用交叉熵损失
    optimizer = optim.SGD(model.parameters(), lr=lr, momentum=momentum)
    criterion = nn.CrossEntropyLoss()
    for epoch in range(1, epochs + 1):
        # TODO 训练 and test
        train(model, train_loader, optimizer, criterion, epoch)
        test(model, test_loader, criterion)


def main():
    train_and_test(model=model, train_loader=train_loader, test_loader=test_loader, epochs=epochs, lr=lr,
                   momentum=momentum)
    # 模型训练完成后，保存
    torch.save(model.state_dict(), model_file)
