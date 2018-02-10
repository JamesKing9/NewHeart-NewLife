web.xml

```xml
<servlet-mapping>
  <servlet-name></servlet-name>
  <url-pattern></url-pattern>
</servlet-mapping>

<filter-mapping>
  <filter-name></filter-name>
  <url-pattern></url-pattern>
</filter-mapping>
```



`<url-pattern>` 的解析规则，Servlet 和 Filter 一样， 匹配的规则有 3 种：

- 精确匹配：如，`/foo.htm` 只会匹配 `foo.htm` 这个 URL。
- path match： 如， `/foo/*` will match 以foo为前缀的URL。
- 后缀 match：如，`*.htm` will match 所有以`.htm` 为后缀的URL.




Servlet 的匹配规则在 `org.apache.tomcat.util.http.mapper.Mapper.internalMapWrapper` 中定义.



Filter 的匹配规则在 `ApplicationFilterFactory.matchFiltersURL` 方法中定义.