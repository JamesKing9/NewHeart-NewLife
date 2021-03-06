[TOC]

# 5-Preparing the Page Views and Controller Servlet

This tutorial unit demonstrates how to create project files in the IDE, and introduces you to some of the facilities available for HTML and CSS development. After creating necessary project files, you begin organizing the front-end of the application. That is, you'll place JSP files in their proper locations within the project structure, create a header and footer which will be applied to all views, and set up the controller servlet to handle incoming requests.

In this unit, you also create a web deployment descriptor (web.xml file) for the application. You can use the deployment descriptor to specify configuration information which is read by the server during deployment. Although the Servlet 3.0 Specification, included in Java EE 6, enables you to use class annotations in place of XML, you may still require the deployment descriptor to configure certain elements of your application. Specifically, in this unit you add directives for the header and footer and specify which files they will be applied to.

One of the goals of this tutorial unit is to create JSP pages that correspond to the views specified in the application design. Referring back to the page mockups and process flow diagram, you begin implementing page layouts according to the mockups by creating placeholders for all visual and functional components. This unit provides a guide for implementing the layout of the welcome page. You can apply the outlined steps to create the other pages on your own, or download project snapshot 1, which provides completed layouts for all pages.



## Creating Project Files

To create new files for your project, access the IDE's `File`  wizard. You can click the `New File` (![New File button](https://netbeans.org/images_www/articles/73/javaee/ecommerce/common/new-file-btn.png)) button, press `Ctrl-N (⌘-N on Mac)`, or in the `Projects` window, right-click the folder node that will contain the new file, and choose `New > [file-type]`. In the following sub-sections, create `JSP` pages and a stylesheet for the project.

### Creating JSP Pages

Begin working in the project by creating JSP pages that correspond to the views displayed in the [process flow diagram](https://netbeans.org/kb/docs/javaee/ecommerce/design.html#business).

The `index.jsp` page that was generated by the IDE will become the project's welcome page. Create JSP pages for the four remaining views and, for  now, place them in the project's webroot with `index.jsp`.

1. Click the `New File` ( ![New File button](https://netbeans.org/images_www/articles/73/javaee/ecommerce/common/new-file-btn.png) ) button to open the File wizard.
2. Select the `Web` category, then select `JSP` and click `Next`.
3. Name the file '`category`'. Note that the Location field is set to `Web Pages`, indicating that the file will be created in the project's webroot. This corresponds to the project's `web` folder, which you can later verify in the IDE's `Files` window.
4. Click `Finish`. The IDE generates the new JSP page and opens it in the editor.
5. Repeat steps 1 - 4 above to create the remaining `cart.jsp`,  `checkout.jsp`, `confirmation.jsp` pages.
  When you finish, your Projects window will look as follows:
  ![Projects window displaying 'view' folder and JSP pages](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/projects-win-views.png) 

### Creating a Stylesheet

Create a CSS file to contain all styles specific to the application.

1. In the `Projects` window, right-click the `Web Pages` node and choose `New > Folder`.
2. In the `New Folder` wizard, name the folder '`css`' and click `Finish`.
3. Right-click the new `css` folder and choose `New > Cascading Style Sheet`. (If the `Cascading Style Sheet` item is not listed, choose `Other...` In the File wizard, select the `Web` category, then select `Cascading Style Sheet` and choose `Next`.)
4. Name the stylesheet `affablebean`, then click `Finish`. When you finish, you'll see the `affablebean.css` file displayed in your `Projects` window.
   ​                    ![Projects window displaying 'affablebean.css' stylesheet](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/projects-win-css.png)

## Implementing HTML and CSS content

The purpose of this section is to design the page views so that they begin to            mirror the provided [page mockups](https://netbeans.org/kb/docs/javaee/ecommerce/design.html#mockups). As such,            they'll serve as a scaffolding which you can use to insert dynamic content during            later stages of project development. To do so, you'll utilize the IDE's HTML            and CSS editors, along with several CSS support windows.

> **Browser compatibility note:** This tutorial uses            Firefox 3 and *does not* guarantee that page view markup is compatible            with other modern browsers. Naturally, when working with front-end web technologies            (HTML, CSS, JavaScript) you would need take measures to ensure that your web            pages render properly in the browsers and browser versions that you expect visitors            to your site will be using (typically Internet Explorer, Firefox, Safari, Chrome,            and Opera). When working in the IDE, you can set the browser you want your application            to open in. Choose Tools > Options (NetBeans > Preferences on Mac), and under            the General tab in the Options window, select the browser you want to use from            the Web Browser drop-down. The IDE detects browsers installed to their default            locations. If a browser installed on your computer is not displayed, click the            Edit button and register the browser manually.

Preparing the display of your web pages is usually an iterative process which you would fine-tune with regular feedback from the customer. The following steps are designed to introduce you to the facilities provided by the IDE, and demonstrate how to get started using the [welcome page mockup](https://netbeans.org/kb/docs/javaee/ecommerce/design.html#index) as an example.

1. In the Projects window, double-click `index.jsp` to open it in the editor.
2. Begin by creating `<div>` tags for the main areas of the page. You can create five tags altogether: four for main areas (header, footer,left column, and right column), and the fifth to contain the others. Remove any content within the `<body>` tags and replace with the following. 

```html
 <body>
    <div id="main">
        <div id="header">
            header
        </div>

        <div id="indexLeftColumn">
            left column
        </div>

        <div id="indexRightColumn">
            right column
        </div>

        <div id="footer">
            footer
        </div>
    </div>
</body>
```

3. Add a reference to the stylesheet in the page's `<head>` tag, and change the title text.
```html
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <link rel="stylesheet" type="text/css" href="css/affablebean.css">
    <title>The Affable Bean</title>
</head>
```

4. Open the `affablebean.css` stylesheet in the editor. Begin creating style rules for the `<div>` IDs you just created. 
  - Use the `width` and `height` properties to create space for each area.
  - Use the `background` property to discern the areas when you  view the page.
  - In order to horizontally center the four areas in the page, you can include `margin: 20px auto` to the `body` rule. (`20px` applies to the top and bottom; `auto` creates equal spacing to the left and right.) Then include `float: left` to the left and right columns.
  - The `footer` requires `clear: left` so that its top border displays after the bottom borders of any left-floating areas above it (i.e., the left and right columns).
```css
body {
    font-family: Arial, Helvetica, sans-serif;
    width: 850px;
    text-align: center;
    margin: 20px auto;
}

#main { background: #eee }

#header {
    height: 250px;
    background: #aaa;
}

#footer {
    height: 60px;
    clear: left;
    background: #aaa;
}

#indexLeftColumn {
    height: 400px;
    width: 350px;
    float: left;
    background: #ccc;
}

#indexRightColumn {
    height: 400px;
    width: 500px;
    float: left;
    background: #eee;
}
```

5. Click the Run Project ( ![Run Project button](https://netbeans.org/images_www/articles/73/javaee/ecommerce/common/run-project-btn.png) ) button in the IDE's main toolbar. Project files that containchanges are automatically saved, any Java code in the project compiles, the project is packaged and deployed to  GlassFish, and your browser opens to display the current state  of the welcome page. ![Welcome page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/index-page.png)

6. Now, begin creating `placeholders` for `page components` within each of the four visible areas. 

  Start with the `header`. Reviewing the **welcome page mockup**, the `header` should contain the following components: 

  - logo
  - logo text
  - shopping cart widget
  - language toggle

  ![welcome page](https://netbeans.org/images_www/articles/73/javaee/ecommerce/design/mockup-index-small.png)

  Make the following changes to the `index.jsp` file. Let the following code replace the `header ` placeholders :

  ```html
  <div id="header">
      <div id="widgetBar">

          <div class="headerWidget">
              [ language toggle ]
          </div>

          <div class="headerWidget">
              [ shopping cart widget ]
          </div>

      </div>

      <a href="#">
          <img src="#" id="logo" alt="Affable Bean logo">
      </a>

      <img src="#" id="logoText" alt="the affable bean">
  </div>
  ```

  In the above code, you use a `<div id="widgetBar">` element to contain the the language toggle and shopping cart widget.

  > ### NetBeans HTML Editor Support
  >
  > When you work in the editor, take advantage of the IDE's HTML support.                        Aside from typical syntax highlighting that lets you differentiate                        between tags, attributes, attribute values, and text, there are plenty                        of other features.
  >
  > When typing tags and attributes in the editor, you can invoke code-completion                        and documentation support by pressing Ctrl-Space. The IDE presents a list                        of suggestions which you can choose from, as well as a documentation window                        that defines the selected item and provides code examples.![](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/documentation-popup.png)
  >
  > The IDE detects errors in your code and provides you with warnings, error                        messages, and in some cases, suggestions. Warning messages are displayed                        in yellow, while errors are shown in red. You can hover your pointer over                        a designated area to view the message in a tooltip.![](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/html-hint.png)
  >
  > You can also take advantage of numerous keyboard shortcuts. Choose Help >                        Keyboard Shortcuts Card from the main menu.

7. In the stylesheet, create rules for the new IDs and classes. Add the following rules beneath the `header` rule.


```css
#header {
    height: 250px;
    background: #aaa;
}

#logo {
    height: 155px;
    width: 155px;
    float: left;
    margin-left: 30px;
    margin-top: -20px;
}

#logoText {
    float: left;
    margin: 20px 0 0 70px;
    /* font styles apply to text within alt tags */
    font-family: 'American Typewriter', Courier, monospace;
    font-size: 50px;
    color: #333;
}

#widgetBar {
    height: 50px;
    width: 850px;
    float: right;
    background: #ccc;
}

.headerWidget {
    width: 194px;
    margin: 20px 2px;
    font-size: small;
    float: right;
    line-height: 25px;
    background: #aaa;
}
```

For the `logo` rule, you apply `margin-left` and `margin-top` properties to position the component on the page.

> If there are properties in the above code that you are unfamiliar with, position your cursor on the given property and press `Ctrl-Space` to invoke a pop-up window that provides documentation support. 
>
> ![](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/css-doc-support.png)
>
> To see how a property is affecting your page, you can comment it out, then refresh the page in the browser. To comment out code, position your cursor on a line, or highlight a block of code, then press Ctrl-/ (⌘-/ on Mac).



8. Save (Ctrl-S; ⌘-S on Mac) the `index.jsp` and `affablebean.css` files, then switch to your browser and refresh the page to view its current state. 

![](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/index-page2.png)

> Note: The IDE's 'Deploy on Save' facility is automatically activated for Java web projects. This means that every time you save a file, the file is automatically compiled (i.e., if it is a Java class or JSP page) and the project is newly packaged and deployed to your server. Therefore, when you make HTML or CSS changes, you don't need to explicitly rerun the project to view the updated version in a browser. Simply save your file(s), then switch to the browser and refresh the page.



By following the previous steps, you are probably able to see a pattern emerging. For each area on the page, you perform three steps:

1. Create the structure in HTML.
2. Create a set of styles to define the appearance.
3. View the page to examine the results of your changes.

Following these three steps, let's implement the components in the remaining areas.



9. Create placeholders for components in the right column. According to the **welcome page mockup**, the right column contains four evenly-spaced boxes.

Create the structure for the four boxes. Insert the following code between the `<div id="indexRightColumn">` tags.

```html
<div id="indexRightColumn">
    <div class="categoryBox">
        <a href="#">
            <span class="categoryLabelText">dairy</span>
        </a>
    </div>
    <div class="categoryBox">
        <a href="#">
            <span class="categoryLabelText">meats</span>
        </a>
    </div>
    <div class="categoryBox">
        <a href="#">
            <span class="categoryLabelText">bakery</span>
        </a>
    </div>
    <div class="categoryBox">
        <a href="#">
            <span class="categoryLabelText">fruit & veg</span>
        </a>
    </div>
</div>
```

10. Add style rules to `affablebean.css` for the new `categoryBox` and `categoryLabelText` classes.

```css
#indexRightColumn {
    height: 400px;
    width: 500px;
    float: left;
    background: #eee;
}

.categoryBox {
    height: 176px;
    width: 212px;
    margin: 21px 14px 6px;
    float: inherit;
    background: #ccc;
}

.categoryLabelText {
    line-height: 150%;
    font-size: x-large;
}
```

> **NetBeans CSS Support**
>
> When working in stylesheets, there are two windows that can be particularly helpful. The CSS Preview enables you to view style rules as they are rendered in a browser. To open the CSS Preview, choose Window > Other > CSS Preview from the main menu. When you place your cursor within a style rule in the editor, the CSS Preview automatically refreshes to display sample text according to the properties defined in the rule.
> ![CSS Preview](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/css-preview.png)
>
> The CSS Style Builder is useful if you do not like to code style rules by hand. To open the CSS Style Builder, choose Window > Other > CSS Style Builder from the main menu. Using this interface, you can construct rules by choosing properties and values from a graphical interface.
> ![CSS Style Builder](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/style-builder.png)
>
> Like the CSS Preview, the Style Builder is synchronized with the editor. When you make a selection in the Style Builder, the style rule is automatically updated in the editor. Likewise, when you type changes into the editor, the selections in the Style Builder are instantly updated.

11.Save (Ctrl-S; ⌘-S on Mac) the index.jsp and affablebean.css files, then switch to your browser and refresh the page to view its current state.
![Welcome page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/index-page3.png)



12.The left column and footer only require placeholders for static text, so let's implement both simultaneously.

Insert the following code between the `<div id="indexLefttColumn">` and `<div id="footer">` tags. 

```html
<div id="indexLeftColumn">
    <div id="welcomeText">
        <p>[ welcome text ]</p>
    </div>
</div>

...

<div id="footer">
    <hr>
    <p id="footerText">[ footer text ]</p>
</div>
```

13.Make changes to the `affablebean.css` stylesheet. It's not necessary to account for all new IDs and classes - you can fine-tune the appearance at a later point when you receive text and images from the customer.

The horizontal rule (<hr>) tag runs the full length of its containing element (`<div id="footer"`). Therefore, to shorten it in accordance with the mockup image, you can adjust the width of `<div id="footer">`. 
```css
#footer {

height: 60px;
width: 350px;
clear: left;
background: #aaa;
}

hr {
border: 0;
background-color: #333;
height: 1px;
margin: 0 25px;
width: 300px;
}
```
14. Save (Ctrl-S; ⌘-S on Mac) the index.jsp and affablebean.css files, then switch to your browser and refresh the page to view its current state.
   ![Welcome page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/index-page4.png) 
   The welcome page is complete. You've created all necessary placeholders for components that will exist on the page.

You've now completed the initial design of the application's welcome page. All placeholders for page components exist. Later in the tutorial, when you begin to apply dynamic logic to the page views, you can simply plug JSTL and EL expressions into these placeholders.

The task remains for you to implement the initial design for the other pages based on the mockups. To accomplish this, follow the pattern outlined above, namely:

1. Create <div> tags for the main page areas.
2. Iterate through each area and perform three steps:
  1. Create the structure in HTML.
  2. Create a set of styles to define the appearance.
  3. View the page to examine the results of your changes.

Be sure to take advantage of the HTML and CSS support that the IDE provides for you. Some tips and tricks are outlined below. If you just want to grab the code for the remaining pages and proceed with the tutorial, you can download snapshot 1 of the AffableBean project. Images of initial mockup implementations for the remaining pages are included here.
**category page**
![Category page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/category-page.png)

**cart page**
![Cart page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/cart-page.png)

**checkout page**
![Checkout page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/checkout-page.png)

**confirmation page**
![Confirmation page displayed in browser](https://netbeans.org/images_www/articles/73/javaee/ecommerce/page-views-controller/confirmation-page.png)

>  Note: The background colors for each page area only serve to help you position elements while developing the application. Eventually, you'll want to remove them from the stylesheet and apply a background color more suitable for the application. You can do this by adjusting the background rule for the main class:
```css
#main { background: #f7f7e9 }
```



## Placing JSP Pages in WEB-INF

Looking back at the page mockups that were created, you can see that the welcome page should look the same whenever it is requested, for whomever requests it. That is, the content that displays on the welcome page is not determined by a user's session. (Sessions are discussed in Unit 8, Managing Sessions.) Notice however that all other pages do need some form of user-specific information to display properly. For example, the category page requires that the user select a category in order to display, and the cart page needs to know all items currently held in a shopper's cart. These pages will not render properly if the server isn't able to associate user-specific information with an incoming request. Therefore, we do not want these pages to be accessed directly from a browser's address bar. The project's WEB-INF folder can be used for this purpose: any resources contained in the WEB-INF folder are not directly accessible from a browser.

Create a new folder named `view`, and place it in the `WEB-INF` folder. Then move all JSP pages other than the `welcome page` into this new folder.

To demonstrate that these pages are no longer accessible from a browser, click the **Run Project** button to run the project. When the application displays in your browser, enter the full path to any of these files in the address bar. For example, type in:
```
http://localhost:8080/AffableBean/WEB-INF/view/category.jsp
```
You receive an HTTP Status 404 message, indicating that the resource is not available.