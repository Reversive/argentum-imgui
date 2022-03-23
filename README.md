<h1 align="center">Welcome to argentum-imgui 👋</h1>
<p>
  <a href="https://opensource.org/licenses/MIT" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  </a>
</p>

> ImGui integration for the popular 2D MMORPG Argentum Online
## What is this?
This is an integration of [Dear ImGui](https://github.com/ocornut/imgui) (a bloat-free graphical user interface library for C++) into Argentum Online. For this, it's necessary to hook directx EndScene/BeginScene/Present in order to get the d3d device and pass it to ImGui which provides a wide variety of drawing functions/widgets.  
## Requirements
- [DirectX Software Development Kit](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
- [dxwrapper](https://github.com/elishacloud/dxwrapper) to wrap dx8 calls into dx9 (put the d3d8.dll, dxwrapper.dll and dxwrapper.ini in the game executable directory and enable d3d8to9 setting on dxwrapper.ini)
## Showcase

### Radar PoC


https://user-images.githubusercontent.com/14043761/159783642-b2689318-f98f-4ae9-b76d-5653b68abda7.mp4
#### Note: This isn't included in the repository and will never be, do not send me a message asking how to do this, this is only for educational purposes.



### ImGui Demo Menu
https://user-images.githubusercontent.com/14043761/159626853-49a286e4-5e2a-4ca0-8c0d-0404d8dbbc00.mp4



## Author

👤 **Matias Pavan**

* Github: [@Reversive](https://github.com/Reversive)

## 🤝 Contributing

Contributions, issues and feature requests are welcome!<br />Feel free to check [issues page](https://github.com/Reversive/argentum-imgui/issues). 

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2022 [Matias Pavan](https://github.com/Reversive).<br />
This project is [MIT](https://opensource.org/licenses/MIT) licensed.

NOTE: THIS IS FOR EDUCATIONAL PURPOSES ONLY.
***
