Name:           timer50yen
Version:        1.0
Release:        1%{?dist}
Summary:        Terminal stopwatch/timer app

License:        MIT
URL:            https://github.com/luke50yen/timer50yen
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc
Requires:       pulseaudio

%description
A simple terminal stopwatch/timer with sound notification.

%prep
%setup -q

%build
make

%install
make install DESTDIR=%{buildroot}

%files
/usr/local/bin/timer50yen
%doc README.md
%license LICENSE

%changelog
* Mon Jul 21 2025 Luke50yen <pandalitigd@gmail.com> - 1.0-1
- Initial RPM release