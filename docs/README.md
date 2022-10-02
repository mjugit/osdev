# Project docs
Below this directory you will find - as the name suggests - the project documentation. In the interest of good manageability, it has been divided into different sections, each dealing with one topic. The `README.md` file in each section directory provides a summary and a table of contents. To play to the strengths of hypertext, relative links were used in the Markdown files. Depending on the software you use for reading outside of GitHub, you have the possibility to switch back and forth between the documents there as well. I personally use Emacs in `markdown-mode` and can use the documents pretty much like a web page.

## General
This section deals with the basic mechanics and concepts that are used during the development process.
- [**Building the project**](./concepts/building-the-project.md)  
  How the build process works and why you need a cross-compiler.
- [**Text mode graphics**](./concepts/text-mode-graphics.md)  
  The basics of text mode graphics and what to do to make it work.
  
## Programming guide
This section deals with the actual development of the project. It is less about the underlying concepts and more about how to use the existing code. In other words, a comprehensive guide for all newcomers and project participants.

- [**Boot process**](./boot/README.md)  
  Topics related to the boot process, including early kernel tasks.
- [**C library**](./libc/README.md)  
  The C standard library that will later be available to all programs on the system.
- [**Code style**](./code-style.md)  
  A brief digression on the subject of code style.
- [**Kernel library**](./libk/README.md)  
  This library is for kernel functions (not usable within the later userland).
- [**Unit testing**](./testing/README.md)  
  How the project's unit testing solution works, new tests can be created and how to set up a build configuration for them.
