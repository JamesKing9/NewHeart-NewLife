# session
```
在计算机中，尤其是在网络应用中，称为“会话控制”。
Session对象存储特定用户会话所需的属性和配置信息。
```

# JavaScript
学习的链接：`http://www.runoob.com/js/js-syntax.html`
```
JavaScript 是一个脚本语言。

JavaScript web 开发人员必须学习的 3 门语言中的一门：
HTML 定义了网页的内容
CSS 描述了网页的布局
JavaScript 网页的行为

HTML 中的脚本必须位于 <script> 与 </script> 标签之间。
脚本可被放置在 HTML 页面的 <body> 和 <head> 部分中。
```

# JavaScript 数据类型
```
字符串（String）、数字(Number)、布尔(Boolean)、数组(Array)、对象(Object)、空（Null）、未定义（Undefined）。

```

# JavaScript 表单验证
```javascript
/*
HTML 表单验证(validate)可以通过 JavaScript 来完成。
以下实例代码用于判断表单字段(fname)值是否存在，如果存在，则弹出信息，否则阻止表单提交.
*/
function validateForm() {
  var x = document.forms["myForm"]["fname"].value;
  if(x==null || x == "") {
    alert("输入名字。");
    return false;
  }
}
```
```html
/*
可以通过 HTML 代码来调用JavaScript代码。
*/
<form name="myForm" action="demo_form.php" onsubmit="return validateForm()" method="post">
名字：<input type="text" name="fname">
<input type="submit" value="提交">
</form>
```

# JavaScript 注释
```
可以添加注释来对 JavaScript 进行解释，或者提高代码的可读性。
单行注释以 // 开头。
多行注释以 /* 开始，以 */ 结尾。
```

