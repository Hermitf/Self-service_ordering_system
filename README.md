**配置**：

1. 在VS中右键点击属性，在`C/C++`写入mysql的include目录
2. 并在`常规-附加库目录`写入mysql的lib目录
3. 与此同时，在`输入-附加依赖项`中，写入libmysql.lib文件

**注意**：

1. 有些界面带有中文，由于我使用的是VS，因此在该文件中有中文时，需在`文件-高级保存选项`将编码改为Unicode 代码页1200。

2. 由于我是在VS中写的QT，因此有需要者，可去网上参考相关的文章，如何利用QT相关插件，在VS中写QT。