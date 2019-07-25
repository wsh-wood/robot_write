import torch
import torch.nn as nn
import torch.optim as optim
from data import getData
from module import Cnn
from func import train, test

model = Cnn(1, 10)
train_loader, test_loader = getData()
epochs = 12  # 训练次数
lr = 0.001  # 学习率
momentum = 0.6  # 动量
model_file = 'model_file'
log_interval = 20


def train_and_test(model, train_loader, test_loader, epochs
                   , lr, momentum, log_interval):
    # 优化算法用SGD，损失函数用交叉熵损失
    optimizer = optim.SGD(model.parameters(), lr=lr, momentum=momentum)
    criterion = nn.CrossEntropyLoss()
    for epoch in range(1, epochs + 1):
        train(model, train_loader, optimizer, criterion, epoch, log_interval)
        test(model, test_loader, criterion)


def main():
    train_and_test(model=model, train_loader=train_loader, test_loader=test_loader, epochs=epochs, lr=lr,
                   momentum=momentum, log_interval=log_interval)
    # 模型训练完成后，保存
    torch.save(model.state_dict(), model_file)


if __name__ == '__main__':
    main()
