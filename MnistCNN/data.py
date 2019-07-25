from torch.utils.data import DataLoader
import torchvision.transforms as transforms
from torchvision import datasets

batch_size = 128


def getData():
    # 下载训练集MNIST手写数字训练集
    train_dataset = datasets.MNIST(
        root='./data',  # 数据保持的位置
        train=True,
        transform=transforms.ToTensor(),  # 一个取值范围是[0,255]的PIL.Image转化为取值范围[0,1]的torch.FloadTensor
        download=True
    )
    test_dataset = datasets.MNIST(
        root='./data',
        train=False,
        transform=transforms.ToTensor()
    )
    # 数据处理尺寸大小为batch_size = 128，
    # 在训练集中，shuffle必须为True，表示次序是随机的
    train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
    test_loader = DataLoader(test_dataset, batch_size=batch_size, shuffle=True)
    return train_loader, test_loader
