### Software Licensing

_formal definition: legal document governing the use or redistribution of software_

Open source software generally has two camps of licenses and one middle ground that is a little unique. The two big ones are known as **copyleft** and **non-copyleft**.

---

##### What is copyleft?

For background, **copyright** means something along the following: "this is my stuff, and if you want to use it, you need a license; you might even have to pay me."

_formal definition: the exclusive legal right, given to an originator or an assignee to print, publish, perform, film, or record literary, artistic, or musical material, and to authorize others to do the same._

**copyleft** essentially says "this is my stuff, you can use it ... possibly even pay me to use it ... but then anyone else can use it too"

_formal definition: an arrangement whereby software or artistic work may be used, modified, and distributed freely on condition that anything derived from it is bound by the same condition._

##### An example of copyleft

I write code and release it with a **non-copyleft** license.  Company A cuts and pastes the code into a project, sells the software to customers.  They are under no obligation to the release the source code to that new software.

-- or --

I write code and release it with a **copyleft** license.  Company B cuts and pastes the code into a project, sells the software to customers.  They are required to release the source code to that new software to customers.

Hypothetically, Company C takes the code from Company B, cuts and pastes it, and sells the software to customers.  They are then also required to release the source code to customers.

**copyleft** "carries" the open source license with it, wherever it is cut & pasted. i.e if you take this code, your code is now required to be open source if you "distribute" the software.

##### Reasoning between one over the other

**copyleft** says the open source-ness of the code sort of continues forever. **non-copyleft** says, if you want to take the code, modify it, cut & paste it, whatever, you never have to release it if you don't want to.

The reasons for preferring one over the other are plenty, but one of the biggest ones is really a question of principle:

If I release code as open source, then people should be able to do whatever they want with it ... why force them to release their new code?

-- or --

If i release code open source, i don't want some company to just use my code to make money ... they gotta release their code too.

##### An example of the pros/cons of copyleft licenses

Some companies, lets say Microsoft, would be FRIGHTENED of copyleft software.  They don't want the risk that they accidentally cut & paste any copyleft software into their software, because then they are obligated to release their code. So some companies require all of their engineers to NEVER look at copyleft software code.  That's a lot of developers that can never look at your code if you release it with a **non-copyleft** license.

##### GPL

GPL is one of the most famous **copyleft** licenses. This license guarantees end users the ability to run, study, share, and modify the software. They include famous software like the Linux kernel and `gcc`.

##### BSD and Apache

BSD and Apache are some of the most famous **non-copyleft** licenses. From the BSD's Wikipedia page:

> The BSD license is a simple license that merely requires that all code retain the BSD license notice if redistributed in source code format, or reproduce the notice if redistributed in binary format. The BSD license (unlike some other licenses) does not require that source code be distributed at all.

##### LGPL

LGPL says basically, "this code is GPL, BUT if it's a library and you want to link to it ... it's ok.  Your code won't become copyleft or GPL."

From its Wikipedia definition:

> The license allows developers and companies to use and integrate a software component released under the LGPL into their own (even proprietary) software without being required by the terms of a strong copyleft license to release the source code of their own components.

An example LGPL project is [flux-core](https://github.com/flux-framework/flux-core).

---

Given these three classes of licenses, we can say that **non-copyleft** code can be copied into a **copyleft** project, but we _can not_ say that **copyleft** code can be copied into a **non-copyleft** project, because that would in fact turn it into a **copyleft** project.

One of the main takeaways from licensing is to remember to do your research before cutting & pasting code. It's important to be able to recognize the implications that certain licenses have on their software, even if it is the same "class" of license, but the version differs (i.e GPLv2 vs. GPLv3).

[This](https://choosealicense.com/appendix/) website has a table where you can compare licenses to one another to see which actions are permissible under which license when making a decision on how to release your software. 
