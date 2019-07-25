import torch.nn as nn
import torch.nn.functional as F


# 创建卷积神经网络
class Cnn(nn.Module):
    def __init__(self, in_dim, n_class):  # in_dim是传入图片的通道数，n_class是最终输出数据的种类，在数字识别中有10个数字
        super().__init__()
        self.conv = nn.Sequential(
            nn.Conv2d(1, 32, 3),  # 第一层通道为1，卷积层为32，卷积核大小为3*3
            nn.BatchNorm2d(32),
            nn.ReLU(True),  # 激活函数用ReLU
            # nn.MaxPool2d(2, 2),  # 池化层用2*2最大池化
            nn.Conv2d(32, 64, 3),  # 第二层卷积用32通道，64层，大小为3*3
            nn.BatchNorm2d(64),
            nn.ReLU(True),
            nn.MaxPool2d(2, 2),
            nn.Dropout2d(),
        )
        self.fc = nn.Sequential(
            nn.Linear(12 * 12 * 64, 128),
            nn.Dropout2d(),
            nn.Linear(128, n_class)
        )

    def forward(self, x):  # x为输入的图片
        x = self.conv(x)
        x = x.view(-1, 12 * 12 * 64)  # 卷积池化完成以后需要将其展开，第一个参数为-1，就是默认维度的意思，out.size是你输入图片的维度。
        x = self.fc(x)
        return F.log_softmax(x, dim=1)  # 将得出的值返回成一个
        # return x

# 打印模型检查是否有错
# model = Cnn(1, 10)
# print(model)
