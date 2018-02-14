
element a href


```html
<a href="https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/href" tabindex="1">href</a>
```

The `href` attribute defines a link to a resource as a reference URL. The exact meaning of that link depends on the context of each element using it.

# `<a>`

The HTML `<a>` element (or anchor element) creates a hyperlink to other web pages, files, locations within the same page, email addresses, or any other URL.

## Attributes

### **target**

Specifies where to display the linked URL. It is a name of, or **keyword** for, a browsing context: a tab, window, or `<iframe>`. The following **keywords** have special meanings: 

- `_self`: Load the URL into the same browsing context as the current one. This is the default behavior.
- `_blank`: Load the URL into a new browsing context. This is usually a tab, but users can configure browsers to use new windows instead.
- `_parent`: Load the URL into the parent browsing context of the current one. If there is no parent, this behaves the same way as `_self`.
- `_top`: Load the URL into the top-level browsing context (that is, the "highest" browsing context that is an ancestor of the current one, and has no parent). If there is no parent, this behaves the same way as `_self`.

> **Note:** When using `target`, consider adding `rel="noopener noreferrer"` to avoid exploitation of the `window.opener` API.