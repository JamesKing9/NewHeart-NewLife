# Java对Excel表格的操作

目前软件开发多采用B/S架构。

B/S架构可以给软件的开发部署带来很大的便利，但是与此同时这种架构也带来了一些问题，例如, Web报表的处理等，在B/S架构下，客户端的开发并没有丰富的、互动性能良好的界面组件供开发人员调用，而且调用客户端机器上的设备也很不方便。这些缺陷将会导致B/S架构的软件在客户端的一些功能开发陷入困境。

Web报表的开发是一个比较常见的功能，然而在B/S架构上实现这些功能并没有在C/S架构上那么简单，针对这样的问题，在下面的内容中将介绍JSP与Excel的交互、图形报表的制作和基本的Web打印功能，这些功能都不是很难，可以在掌握这些功能的基础上举一反三，思考其他新的应用。

# 1 JSP对Excel报表的处理

在应用系统开发的过程中，很多客户会提出把数据表格导出为Excel文件的需求，这样就可以利用Excel的强大功能做一些统计计算。Java自带的API中并没直接操作Excel文档的方法，如果要在Java中处理Excel文档只有借助于第三方的解决方案。在接下来的章节中将要介绍的就是利用这些第三方的类库处理Excel文档的具体方法。

##  1.1 JSP操作Excel工具汇总

在Java处理Excel这个领域已经有很多开源的解决方案,目前在这方面做得比较出色的有`ApachePOI`和`JExcelApi(jxl)`。

`ApachePOI`是Apache基金组织Jakarta项目的子项目。POI包括一系列的API，可以操作多种格式的Microsoft Office文件，通过这些API可以在Java中很方便地读写Excel、Word等文件。POI是比较完整的Java Excel和Java Word解决方案。其子项目包括：POIFS、HSSF、HDF、HPSF。其中HSSF是Java到Microsoft Excel97/2002文件的接口，支持读写功能。

JExcelApi也是一个Java操作Excel的接口。它也是一个开源的解决方案，虽然在名气方面比不上大名鼎鼎的ApachePOI,但是在操作Excel的功能上丝毫不比POI逊色，而且在某些方面做得比POI更出色，例如生成Excel文件时给合并单元格加边框的问题，在POI中这很难实现的，POI的官方仅仅承诺在以后的版本中会添加这个功能。然而在JExceApi中通过一个简单的设置语句就可以实现。而且总体上JExcelApi使用都是比较简单方便的。

利用Java进行开发，尤其当使用第三方类的库进行开发的时候，最让人头疼的就是中文乱码问题，在这方面就连Apache POI也不例外，在生成Excel文件时必须经过复杂的编码设置才能看到中文显示。但是使用JExcelApi就没有这个问题，只需要简单的选择即可生成漂亮的中文Excel文件，这也是很多开发人员愿意选择这个API的又一个重要原因。

采用这两种工具都可以很方便地操作Excel文件，在这里只介绍JExcelApi的使用方法，其他类似的第三方类库在使用方法上都很类似，参考其文档都是很容易学习的。

## 1.2 JExcelAPi开发环境简单配置

JExcelAPi是一个开源的项目，可以在官方网站下载其最新版本。在JExcelAPi的官方网站上提供各种版本的下载，例如要下载版本为2.4.2的JExcelApi,下载下来的文件为：

Jexcelapi-2-4-2.tar.gz,直接解压这个压轴文件即可。

其中docs目录下是类库参考档案。Src目录下是整个JExcelAPi的源代码，在src目录下有demo子目录，里面是例子代码，demo中的源代码对初学者来说是最好的教材，参考其中的例程可以实现其绝大部分功能。

`JExcelAPi`这个目录下面可以看到`jx1.jar`文件，这个文件就是JExcelAPi打包的类库文件，如果要在项目中使用JExcelAPi只需要把jx1.jar文件的路径加入classpath中或项目`lib`目录下。

## 1.3 JSP生成Excel报表

在接下讲解在JSP中使用JExcelApi生成不同格式的Excel文件.在WEB应用开发过程中，可能会遇到各种各样的报表需求，这些报表不仅布局格式复杂，而且数据类型也是多种多样，甚至有些报表需要在指定的位置显示图片。当这些报表需要导出为Excel的时候，相应的的问题就会出现，而接下来要阐述的内容就是怎样使用JExcelApi来解决这些问题。解决任何问题的时候都是从简单到复杂，下面几个示例也是按照这个原则组织的。

在实际应用开发中，经常需要把指定的数据生成Excel文件，并且可以下载生成的Excel文件。在本章的示例中。利用JavaBean生成的Excel文件，在JSP页面上调用这个JavaBean生成的Excel文件，然后提供下载方式。当访问这个JSP页面的时候可以直接下载生成的Excel文件。

### 1.3.1 JSP生成简单的Excel文件

假设下面这种情形，要把表中的内容导出为Excel文件。

| 学校         | 专业       | 专业竞争力 |
| ------------ | ---------- | ---------- |
| 清华大学     | 计算机专业 | 高         |
| 北京大学     | 法律专业   | 中         |
| 北京理工大学 | 航空专业   | 低         |

在表中展示的内容格式全是字符串。而且这个表格的格式也是相当简单，没有任何合并的单元格，也没有颜色的设置。类似这种表格生成对应的Excel文件是非常容易的，实现这个功能的JavaBean代码如下所示。

```java
package beans.excel;

import java.io.IOException;
import java.io.OutputStream;

import jxl.Workbook;
import jxl.write.Label;
import jxl.write.WritableCellFormat;
import jxl.write.WritableSheet;
import jxl.write.WritableWorkbook;
import jxl.write.WriteException;
import jxl.write.biff.RowsExceededException;

public class SimpleExcelWrite {
    
    public void createExcel(OutputStream os) 
        throws WriteException, IOException {
    	//创建工作薄
    	WritableWorkbook workbook = Workbook.createWorkbook(os);
    	//创建新的一页
		WritableSheet sheet = workbook.createSheet("First Sheet", 0);
        
        //创建要显示的具体内容
        /*
        在工作区（WorkBook）中创建新的一页（Sheeet）其中新建的页（Sheet）名称为“First sheet”。这一页的属性是可以进行写操作的。在JExcelAPi中也可以创建只读的页。
        */
		Label xuexiao = new Label(0, 0, "学校");
		sheet.addCell(xuexiao);
		Label zhuanye = new Label(1, 0, "专业");
		sheet.addCell(zhuanye);
		Label jingzhengli = new Label(2, 0, "专业竞争力");
		sheet.addCell(jingzhengli);
		
		Label qinghua = new Label(0, 1, "清华大学");
		sheet.addCell(qinghua);
		Label jisuanji = new Label(1, 1, "计算机专业");
		sheet.addCell(jisuanji);
		Label gao = new Label(2, 1, "高");
		sheet.addCell(gao);
		
		Label beida = new Label(0, 2, "北京大学");
		sheet.addCell(beida);
		Label falv = new Label(1, 2, "法律专业");
		sheet.addCell(falv);
		Label zhong = new Label(2, 2, "中");
		sheet.addCell(zhong);
		
		Label ligong = new Label(0, 3, "北京理工大学");
		sheet.addCell(ligong);
		Label hangkong = new Label(1, 3, "航空专业");
		sheet.addCell(hangkong);
		Label di = new Label(2, 3, "低");
		sheet.addCell(di);
        
	    /* 这3行代码执行的操作是把工作区中的内容写到输出流中，然后关闭工作区，最后关闭输出流 */
		workbook.write();
		workbook.close();
		os.close();
    }
}
```



下面来看如何在JSP页面上调用这个JavaBean，并且实现下载的功能。具体的JSP代码如下所示。

```jsp
<%@ page language="java" import="java.util.*" pageEncoding="gb2312"%>
<%@ page import="java.io.*" %>
<%@ page import="beans.excel.*" %>
<%
    String fname = "学校专业竞争力情况";
	OutputStream os = response.getOutputStream();//取得输出流
	response.reset(); //清空输出流

    //下面是对中文文件名的处理
	response.setCharacterEncoding("UTF-8");
    fname = java.net.URLEncoder.encode(fname, "UTF-8");
	response.setHeader("Content-Disposition", "attachment; filename="+ new String(fname.getBytes("UTF-8"), "GBK") + ".xls");
    response.setContentType("application/msexcel");//定义输出类型
    SimpleExcelWrite sw = new SimpleExcelWrite();
    sw.createExcel(os);
 %>
<html>
 <body>  
 </body>
</html>
```

