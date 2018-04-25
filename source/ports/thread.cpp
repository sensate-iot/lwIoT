/*
 * Thread wrapper class for the system thread implementation.
 *
 * @author Michel Megens
 * @email  dev@bietje.net
 */

#include <stdlib.h>
#include <string.h>

#include <lwiot/lwiot.h>
#include <lwiot/thread.h>
#include <lwiot/log.h>

namespace lwiot
{
	void thread_starter(void *arg)
	{
		auto *ctx = (Thread*)arg;

		ctx->run(ctx->argument);
		ctx->kill();
	}

	Thread::Thread(const char *name, void *argument)
	{
		size_t length;

		this->running = false;
		this->argument = argument;

		length = strlen(name);
		this->internal.name = (char*)malloc(length + 1);
		memcpy((void*)this->internal.name, name, length + 1);
	}

	Thread::~Thread()
	{
		if(this->running) {
			print_dbg("Deleting running thread!");
		}

		this->stop();
		free((void*)this->internal.name);
	}

	void Thread::kill()
	{}

	void Thread::start()
	{}

	void Thread::stop()
	{
		this->running = false;
	}
}
