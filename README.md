<div align="center">
<h1 style="border-bottom:0"> Simple HTML Include Tool</h1>
<p>Also known as SHIT</p>
</div>

---

### A quick sales pitch:

Tired of being forced to learn and use stupid shit like [Jekyll](https://jekyllrb.com/), [Hugo](https://gohugo.io/), [Hexo](https://hexo.io/), and [Gatsby](https://www.gatsbyjs.com/docs/glossary/static-site-generator/), when you just want to glue a few HTML templates together? Use this SHIT instead!

SHIT is a tiny tool I wrote in C++ to solve the issue of generating static sites without any special features or insane overhead. What you see is what you get: you can write a bunch of separate HTML template files and then compile them into a final static site. Benefits include not re-writing your SEO on every page and having complete control over what you're actually serving to users.

Anyway, in case you don't know how to read full sentences:

### What does it do?

- Compiles multiple HTML files into a single output file using a simple template tag.

### What doesn't it do?

- Process markdown
- Inject random bullshit into your HTML
- Minify anything
- Optimize the site in any way whatsoever
- Keep you safe from yourself (eldritch horror recursive template fork bomb, anyone?)
- Any other useless bullshit

### How to Use It?

I'm about to blow your fucking mind: there's no wiki. This thing isn't complicated enough to need one.

In your HTML files, you can include other HTML files (or really any text file, it's not that complicated) by using a special tag, like so!

```html
<% relative_path_to_file %>
```

> Note: right now, SHIT just blindly copies all HTML files into the output directory INCLUDING templates. It may be beneficial to use a file extension like `.shit` for your templates for this reason. 

At compile time, that tag will be replaced with the contents of the specified folder. To compile:

```console
shit.exe -i path_to_import_folder -o path_to_export_folder
```

It'll automatically collect all of the templates in folder A, compile them, and output a complete static-hosting ready website in folder B.

### But why?

Because I'm tired of fucking everything being an overcomplicated "framework." Sometimes you just want to get something done without learning another tool that will be obsolete in 5 years. Now, if you'll excuse me, I'm off to go take a SHIT.