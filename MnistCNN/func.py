import torch
from torch.autograd import Variable


def train(model, train_loader, optimizer, criterion, epochs, log_interval):
    # for epoch in range(epochs):
    #     running_loss = 0.0
    #     running_acc = 0.0
    #     for i, data in enumerate(train_loader, 1):  # 批处理
    #         img, label = data
    #         img = Variable(img)  # 自动求微分
    #         label = Variable(label)
    #         # 前向传播
    #         out = model(img)
    #         loss = criterion(out, label)
    #         running_loss += loss.item() * label.size(0)
    #         _, pred = torch.max(out, 1)  # 预测结果
    #         num_correct = (pred == label).sum()  # 正确结果的数量
    #         running_acc += num_correct.item()  # 正确结果的总数
    #         # 后向传播
    #         optimizer.zero_grad()  # 梯度清零，以免影响其他batch
    #         loss.backward()  # 后向传播，计算梯度
    #         optimizer.step()  # 利用梯度更新w，b
    #     # 打印一次循环后，训练集合上的loss和正确率
    #     print('Train{}epoch,Loss:{:.6f},Acc:{:.6f}'.format(epoch + 1, running_loss / len,
    #                                                        running_acc / len))
    #

    for batch_idx, (data, target) in enumerate(train_loader):
        optimizer.zero_grad()
        output = model(data)
        loss = criterion(output, target)
        loss.backward()
        optimizer.step()

        if batch_idx % log_interval == 0:

            print('Train Epoch: {} [{:6d}/{:6d} ({:2.0f}%)]'
                  '\tLoss: {:.6f}'.format(
                epochs, batch_idx * len(data), len(train_loader.dataset),
                        100. * batch_idx / len(train_loader), loss.item()))


def test(model, test_loader, criterion, ):
    # model.eval()  # 由于训练测试的BatchNorm、Dropout配置不同，需要说明是否模型测试
    # eval_loss = 0
    # eval_acc = 0
    # for data in test_loader:
    #     img, label = data
    #     img = Variable(img, volatile=True)  # volatile确定是否不调用backward(),另外测试不需要label
    #     out = model(img)  # 前向算法
    #     loss = criterion(out, label)  # 计算loss
    #     eval_loss += loss.item() * label.size(0)
    #     _, pred = torch.max(out, 1)
    #     num_correct = (pred == label).sum()
    #     eval_acc += num_correct.data[0]  # 正确结果总数
    # print('Test Loss:{:.6f},Acc:{:.6f}'.format(eval_loss / len_testdata, eval_acc * 1.0 / len_testdata))
    model.eval()
    test_loss = 0
    correct = 0
    cnt = 0
    with torch.no_grad():
        for data, target in test_loader:
            output = model(data)
            test_loss += criterion(output, target).item()
            pred = output.argmax(dim=1, keepdim=True)
            correct += pred.eq(target.view_as(pred)).sum().item()
            cnt += 1

    test_loss /= cnt

    print('\n')
    print('Test set: Average loss: {:.6f}, Accuracy: {}/{} ({:.2f}%)\n'.format(
        test_loss, correct, len(test_loader.dataset),
        100. * correct / len(test_loader.dataset)))
