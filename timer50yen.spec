Name:           timer50yen
Version:        1.2
Release:        1%{?dist}
Summary:        Terminal stopwatch/timer app

License:        MIT
URL:            https://github.com/luke50yen/timer50yen
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc, pkgconfig(libnotify), pkgconfig(glib-2.0)
Requires:       pulseaudio-utils, libnotify

%global debug_package %{nil}
%global _enable_debug_package 0
%global _debugsource_packages 0
%global _debuginfo_packages 0

%description
A simple terminal stopwatch/timer with sound notification.

%prep
%setup -q

%build
make

%install
make install DESTDIR=%{buildroot}

%files
/usr/bin/timer50yen
/usr/bin/t50
/usr/share/timer50yen/alarm.mp3
%doc README.md
%license LICENSE

%changelog
* Mon Jul 21 2025 Luke50yen <pandalitigd@gmail.com> - 1.0-1
- Initial RPM release