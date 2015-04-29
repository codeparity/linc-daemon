Summary: A free, multiplatform authentication client for Cyberoam / 24online
Name: linc-daemon
Version: 1.2
Release: 1
Copyright: GPL
Group: System Environment/Daemons
Source: linc-daemon-1.2.tar.gz
BuildRoot: /var/tmp/%{name}-buildroot
URL: http://linc.sourceforge.net
Packager: Mayur R. Naik <mrnk@users.sf.net>

%description
linc is a free, multiplatform authentication client for Cyberoam / 24online.
Cyberoam is an employee management system for corporate networks. 24online is
a subscriber management system for broadband ISPs.

Install linc if your ISP / company uses Cyberoam for controlling internet
access and you need to connect your *nix box.

%prep
%setup -q

%build
./configure --prefix=$RPM_BUILD_ROOT/usr
make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin

make install
mkdir -p $RPM_BUILD_ROOT/etc/init.d
cp -af linc-srv $RPM_BUILD_ROOT/etc/init.d/linc

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc README TODO COPYING AUTHORS ChangeLog sample.lincrc

/usr/bin/linc
/usr/man/man1/linc.1.gz
/usr/man/man5/lincrc.5.gz
/etc/init.d/linc

%post
chkconfig --add linc
chkconfig --level 2345 linc off
