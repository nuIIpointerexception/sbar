# Maintainer: viable <hi@viable.gg>
pkgname=sbar
pkgver=0.1.0
pkgrel=1
pkgdesc="A suckless simple wayland bar"
arch=('x86_64')
url="https://github.com/nuiipointerexception/sbar"
license=('MIT')
depends=('wayland' 'cairo' 'pango' 'wlroots')
makedepends=('cmake' 'wayland-protocols')
source=("git+${url}.git")
sha256sums=('SKIP')

build() {
	cmake -B build -S ${pkgname} \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=/usr
	cmake --build build
}

package() {
	DESTDIR="$pkgdir" cmake --install build
}
