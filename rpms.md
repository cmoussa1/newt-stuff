## RPM's

A sample file:

```
Name:  powerman
Version: 2.3.25
Release: 1%{?dist}
Summary: PowerMan - centralized power control for clusters
License: GPL
Group: Applications/System
Url: http://github.com/chaos/powerman
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires: tcp_wrappers-devel
BuildRequires: genders
BuildRequires: curl-devel
BuildRequires: net-snmp-devel
BuildRequires: systemd

%package devel
Requires: %{name} = %{version}-%{release}
Summary: Headers and libraries for developing applications using PowerMan
Group: Development/Libraries

%package libs
Requires: %{name} = %{version}-%{release}
Summary: Libraries for applications using PowerMan
Group: System Environment/Libraries
%description
PowerMan is a tool for manipulating remote power control (RPC) devices from a
central location. Several RPC varieties are supported natively by PowerMan and
Expect-like configurability simplifies the addition of new devices.
%description devel
A header file and static library for developing applications using PowerMan.

%description libs
A shared library for applications using PowerMan.

%prep

%setup

%build

%configure \
  --with-genders \
  --with-httppower \
  --with-snmppower \
  --with-tcp-wrappers \
  --with-systemdsystemunitdir=%{_unitdir} \
  --program-prefix=%{?_program_prefix:%{_program_prefix}}
make
%install

rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
%clean

rm -rf $RPM_BUILD_ROOT

%post

/bin/systemctl enable powerman > /dev/null 2>&1 ||:

%post libs
if [ -x /sbin/ldconfig ]; then /sbin/ldconfig %{_libdir}; fi

%preun
if [ "$1" = 0 ]; then
  systemctl stop powerman >/dev/null 2>&1 || :
  systemctl disable powerman > /dev/null 2>&1 || :
fi

%postun
if [ "$1" -ge 1 ]; then
  systemctl try-restart powerman >/dev/null 2>&1 || :
fi

%postun libs
if [ -x /sbin/ldconfig ]; then /sbin/ldconfig %{_libdir}; fi

%files

%defattr(-,root,root,0755)

%doc DISCLAIMER

%doc COPYING

%doc NEWS

%doc TODO

%{_bindir}/powerman
%{_bindir}/pm
%{_sbindir}/powermand
%{_sbindir}/vpcd
%{_sbindir}/httppower
%{_sbindir}/snmppower
%{_sbindir}/plmpower
%dir %config %{_sysconfdir}/powerman
%{_sysconfdir}/powerman/*.dev
%{_sysconfdir}/powerman/powerman.conf.example
%{_mandir}/*1/*
%{_mandir}/*5/*
%{_mandir}/*8/*
%{_libdir}/stonith/plugins/external/powerman
%{_unitdir}/powerman.service
%{_tmpfilesdir}/powerman.conf
%files devel
%defattr(-,root,root,0755)
%{_includedir}/*
%{_libdir}/*.la
%{_mandir}/*3/*
%{_libdir}/*.a
%{_libdir}/*.so
%{_libdir}/pkgconfig/*
%files libs
%defattr(-,root,root,0755)
%{_libdir}/*.so.*
%changelog
* Mon Jan 28 2019 Albert Chu <chu11@llnl.gov> 2.3.25-1
- Support openbmc.dev, kvm.dev, kvm-ssh.dev, rancid-cisco-poe.dev.
```

Let's start at the top: you have **name**, **version**, **summary**, and some other extra info.  If you run `rpm -q -i powerman`, you'll get a lot of that info.

`%buildroot` - that's where you will build your code and source is your source `tar.gz`.  You can also specify patches which can be applied.

`%buildrequires` - this says there are other packages that powerman requires before it is installed. A package manager could install those for the user first.

`%package` - subpackages of the package.

`%prep` - doing setup before the build, typically untar a `tar.gz`

`%build` - typically call configure & make

`%install` - typically call make install

`%clean` - cleanup

`%pre` / `%post` - wrappers to handle extra things, like start powerman after it has been installed. And there are variants like uninstall and stuff

`%changelog` - logging what has changed

`%files` - the files for your package, you'll notice a long list of files here

Basically, we feed this into the `rpmbuild` command, and then it can package things together into an rpm for you.

##### a quick tutorial

create a file **.rpmmacros**:

```
%_topdir        /tmp/moussa1/rpm
%_tmppath       /tmp/moussa1/rpm/TMP
%_target        linux
%prefix         /usr
```

then make some directories:

```
$ mkdir /tmp/$USER
$ mkdir /tmp/$USER/rpm
$ mkdir /tmp/$USER/rpm/BUILD
$ mkdir /tmp/$USER/rpm/RPMS
$ mkdir /tmp/$USER/rpm/SOURCES
$ mkdir /tmp/$USER/rpm/SPECS
$ mkdir /tmp/$USER/rpm/SRPMS
$ mkdir /tmp/$USER/rpm/TMP
```

put the spec file in `/tmp/moussa1/rpm/SPECS/` and the **.tar.gz** in `tmp/moussa1/rpm/SOURCES/`

then from inside `SPECS/`, run: `rpmbuild -ba --with systemd freeipmi.spec`

the `--with systemd` is because the spec file will default to building differently if you don't.

the `-ba` says "build all", which means do the "prep", "build", "install" and maybe more steps that were mentioned earlier.  You can technically do things 1 step at a time if you want.

hopefully you'll see a configure run, then a build happen, then an install eventually happen.

Finally, something at the end like:

```
Wrote: /tmp/achu/rpm/SRPMS/freeipmi-1.6.5-1.ch6_1.src.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-1.6.5-1.ch6_1.x86_64.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-devel-1.6.5-1.ch6_1.x86_64.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-bmc-watchdog-1.6.5-1.ch6_1.x86_64.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-ipmidetectd-1.6.5-1.ch6_1.x86_64.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-ipmiseld-1.6.5-1.ch6_1.x86_64.rpm
Wrote: /tmp/achu/rpm/RPMS/x86_64/freeipmi-debuginfo-1.6.5-1.ch6_1.x86_64.rpm
```

You'll notice a source rpm with source code (`/tmp/moussa1/rpm/SRPMS/freeipmi-1.6.5-1.ch6_1.src.rpm`), and you'll notice files in the `BUILD` and `BUILDROOT` directory.

The buildfarm handles a lot of this stuff for you, you only have to  supply the spec file and tar.gz. The buildfarm will collect em all into `/repo`, and if you look around in there, you'll see a whole bunch of rpms.
