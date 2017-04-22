APP     := mlexer

SRCDIR  := src

OBJDIR  := $(OBJDIR)/$(APP)
SRCSC   := $(shell find $(SRCDIR) -name '*.c')
SRCDIRS := $(shell find . -name '*.c' -exec dirname {} \; | uniq)
OBJS    := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCSC))


all: $(APP)

$(APP) : buildrepo $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BINDIR)/$@

$(OBJDIR)/%.o: %.c
	$(CC) -I$(SRCDIR)/ $(CFLAGS) -c $< -o $@

buildrepo:
	@$(call make-repo)

define make-repo
	for dir in $(SRCDIRS); \
	do \
		mkdir -p $(OBJDIR)/$$dir; \
	done
endef
